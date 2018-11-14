/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 11:39:49 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/10 16:03:41 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_openssl.h"

/*
**	a function to inspect a block's bytes
*/

void	block_inspect(t_block *block)
{
	int i;
	int j;
	int k;
	int r;

	ft_putendl("-------------------------------------------------------");
	i = -1;
	k = -1;
	i = -1;
	while (++i < 8)
	{
		r = k;
		j = -1;
		while (++j < 8)
			ft_printf("%-4c | ", block->text[++k]);
		ft_putchar('\n');
		k = r;
		j = -1;
		while (++j < 8)
			ft_printf("%#4hx | ", block->text[++k]);
		ft_putchar('\n');
		while (++j < 64)
			ft_putchar('-');
		ft_putchar('\n');
	}
}

/*
**	a function to display blocks as they are enqueued or dequeued for testing purposes
*/

void 	block_print(t_block *block, char *base)
{
	ft_printf("block: %d\n", block->count);
	if (!ft_strncmp(base, "ascii", 5))
		ft_printf("block:\n%s\n", block->text);
	else if (!ft_strncmp(base, "inspect", 3))
		block_inspect(block);
	ft_printf("\n");
}

/*
**	given a postion in a string, initializes a new block and copies 64 bytes
**	that position or until a null byte is encountered, the number of copied 
**	bytes will also be assigned to block->length.
**	We also increment the position of the given string here. We need to pass in
** 	a new pointer to avoid a memory leak.
*/

t_block 	*block_new(char **pos, size_t count)
{
	t_block *block;
	int		l;

	block = NULL;
	if (**pos)
	{
		block = ft_memalloc(sizeof(t_block));
		block->text = ft_strnew(64);
		ft_memcpy(block->text, *pos, (l = ft_strlen(*pos)) < 64 ? l : 64);
		*pos += l < 64 ? l : 64;
		block->length = l < 64 ? l : 64;
		block->print = block_print;
		block->count = count;
	}
	return (block);
}


/*
**	break the msg text into 64 byte (512bit) blocks
*/

void	arg_block(t_arg *arg)
{
	int		i;
	char 	*msg;
	t_block	*block;

	arg->blocks = ft_queuenw(NULL, 0);
	msg = arg->msg;		/*the new block function will increment this position, 
						we copy the pointer to maintain the original position 
						thus avoiding a leak*/
	i = -1;
	while ((block = block_new(&msg, ++i)))
	{
		/* just a test to make sure the blocks are bing formed correctly */
		block->print(block, "inspect");
		/*end of test*/

		ft_enqueue(arg->blocks, block, sizeof(t_block));
		free(block);
	}
}

/*
**	pads the argument by placing a bit in front of it and appending 64 more 
**	bits representing the total length of the message
*/

static unsigned char 	g_pad[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

unsigned char	*itos(uint64_t n)
{
	int				i;
	unsigned char	*s;

	s = ft_memalloc(sizeof(unsigned char) * 8);
	i = -1;
	while (++i < 8)
		s[i] = n & (0xff00000000000000 >> (8 * (8 - i)));
	return (s);
}

void			arg_pad(t_arg *arg)
{
	int		i;	
	char	*pad;
	t_block *block;

	pad = ft_strdup(g_pad);
	block = arg->blocks->tail->content;
	/* Append a single bit to the end of the last block if the length allows for it*/
	if (block->length < 64)
		block->text[block->length++] = 0x80;	
	/* Otherwise create a new block and append the bit */
	else
		block = block_new(&pad, block->count + 1);
	
	/*If there's no space left to append the bits make a new block*/
	if (64 - block->length < 8)
	{
		block = block_new(&pad, block->count + 1);
		block->text[0] = 0;
	}
	
	/*Iterate through the bits of the msg length 1 byte at a time and assign
	 the masked values to the ending indecies of the padding text*/
	
	ft_printf("APPENDING BITS\n");
	/*
	i = 8;
	while (--i)
	{
		block->print(block, "inspect");	
		block->text[63 - i] = arg->length & (0x00000000000000ff << (8 * i));
		ft_printf("{\n\tidx: %d,\n\tmask : '0xff << 8 * %d',\n\tmask value: %#x,\n\targ length: %#llx\n}\n",64 - i, i, block->length & (8 * i), arg->length);
	}
	*/
	`
	i = -1;
	while (++i < 8)
	{
		block->print(block, "inspect");
		block->text[63 - i] = arg->length & (0xff << (8 * i));
		ft_printf("{\n\tidx: %d,\n\tmask : '0xff << 8 * %d',\n\tmask value: %#llx,\n\targ length: %#llx\n}\n",64 - i, i, block->length & (0xff << (8 * i)), arg->length);
	}

	/*just a test to make sure the padding block was propperly formed*/
	block->print(block, "inspect");
	/*end of test*/
	
	/*enqueue new block*/
	if (block != arg->blocks->tail->content)
		ft_enqueue(arg->blocks, block, sizeof(t_block));
	
	/*check to see that padding was performed correctly*/
	arg->print(arg);
}

/*
**	prepare the argument by breaking it down into blocks and padding it.
*/

void	arg_prep(t_ssl *ssl, t_arg *arg)
{
	arg->block(arg);
	arg_pad(arg);
}

/*
**	proccess messages
*/

void 	ssl_prep(t_ssl *ssl)
{
	t_expr	*expr;
	t_queue *args;
	t_arg	*arg;

	expr = ssl->expr;
	args = expr->args;
	while ((arg = ft_dequeue(args)) && !arg->prepped)
	{
		arg->prep(ssl, arg);
		arg->prepped = 1;
		ft_enqueue(args, arg, sizeof(t_arg));
		free(arg);
	}
}

/*
** Message digest algorithm
*/
	// Append Padding Bits
	// Append length
	// Initialize MD buffer
	// Proccess Message in 16-word Blocksi
	// Output

/*
** implementation of message digest algorithm 
*/

void	md5(t_ssl *ssl)
{
	ft_printf("function evaluated:%s\n", ssl->expr->cmd.name);
}

/*
**	implementation of sha-256 algorithm
*/

void	sha256(t_ssl *ssl)
{
	ft_printf("function evaluated:%s\n", ssl->expr->cmd.name);
}

/*
**	commandline parsing functions
*/

/*
**	function to retrieve data from stdin
*/

void	get_stdin(t_ssl *ssl)
{
	char	*msg;
	t_expr	*expr;
	t_arg	*args;

	expr = ssl->expr;
	expr->init(ssl);
	msg = NULL;
	if (get_next_line(0, &msg) >= 0)
		expr->argnw(&expr, "stdin", msg);
}

/*
**	retrieves the ssl command from the command line
*/

void	get_cmd(t_ssl *ssl, char **argv)
{
	int	i;
	
	i = -1;
	while (ssl->cmds[++i].name)
		if (!ft_strncmp(ssl->cmds[i].name, argv[1], ft_strlen(ssl->cmds[i].name)))
			ft_memcpy(&(ssl->expr->cmd), &(ssl->cmds[i]), sizeof(t_cmd));
	ssl->eval = ssl->expr->cmd.func;
}

/*
**	retrieve options from cmd
*/

int 	get_ops(t_ssl *ssl, char **argv, int argc)
{
	t_expr	*expr;
	int 	i;
	int		j;
	
	expr = ssl->expr;
	i = 1;
	while (++i < argc && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
		{
			expr->ops |= argv[i][j] == 'p' ? OP_P : 0;
			expr->ops |= argv[i][j] == 'q' ? OP_Q : 0;
			expr->ops |= argv[i][j] == 'r' ? OP_R : 0;
			expr->ops |= argv[i][j] == 's' ? OP_S : 0;
		}
	}
	return (i);
}

/*
**	retrieve remaining arguments from the command line
*/

void	get_args(t_ssl *ssl, int idx, int argc, char **argv)
{
	char	*buf;
	char 	*tmp;
	char 	*msg;
	int 	fd;

	idx--;
	msg = NULL;
	while (++idx < argc)
	{
		if ((fd = open(argv[idx], O_RDONLY)) != -1)
			while (get_next_line(fd, &buf) > 0)
			{
				tmp = ft_strjoin(msg, buf);
				if (msg)
					free(msg);
				msg = ft_strdup(tmp);
				free(tmp);
			}
		else
			msg = ft_strdup(argv[idx]);
		ssl->expr->argnw(&ssl->expr, fd > 0 ? "file" : "arg", msg);
	}
}

/*
**	command line parse must first check for msg txt in stdin and then check for
**	file/stringarguments. For the latter. We will first attempt to see if the
**	string is a file. If yes we will add its contents to our msg_text list. 
**	Otherwise, we will add the string itself
*/


void	ssl_cdl_parse(t_ssl *ssl, int argc, char **argv)
{
	get_stdin(ssl);
	
	/*Just a test to make sure the msg is being enqueued properly*/
	ssl->expr->print(&ssl->expr);
	/*end of test*/

	get_cmd(ssl, argv);
	
	/*just a test to verify command parsing works properly*/
	ft_printf("The command is: %s\n", ssl->expr->cmd.name);
	/*end of test*/

	get_args(ssl, get_ops(ssl, argv, argc), argc, argv);

	/*just a test to make sure options were rretrieved propperly*/
	int o = ssl->expr->ops;
	ft_printf("p: %d, q: %d, r: %d, s: %d\n", o & OP_P, o & OP_Q, o & OP_R, o & OP_S);
	/*end of test*/

	/*Another test to see that the remaining arguments were enqueued*/
	ssl->expr->print(&ssl->expr);
	/*end of test*/
}

/*
**	global variable used to initialize command dispatch table 
*/

t_cmd	g_cmds[3] = {
	{"md5", md5},
	{"sha256", sha256},
	{NULL, NULL}
};

/*
**	argument funtions
*/

/*
**	a function the print the argument, In this case I must pass the 
**	specific argument pointer since there may be many args per ssl instance.
*/

void	argument_print(t_arg *arg)
{
	int i;
	int	l;
	
	ft_printf("arg origin:\t%s\n", arg->origin);
	ft_printf("arg message:\t%s\n", arg->msg);
	
	/*
	i = 0;
	l = ft_strlen(arg->msg);
	while (i < l)
	{
		ft_printf("%.80s\n", arg->msg + i);
		i += 80;
	}
	*/
}

/*
**	function for allocating a new argument and initializing it with a value
*/

t_arg	*argument_new(t_ssl *ssl, char *msg, char *origin)
{
	t_arg	*arg;
	
	arg = ft_memalloc(sizeof(t_arg));
	arg->origin = ft_strdup(origin);
	arg->msg = ft_strdup(msg);
	arg->length = ft_strlen(msg);
	arg->prep = arg_prep;
	arg->prepped = 0;
	arg->block = arg_block;
	arg->print = argument_print; 
	return (arg);
}

/*
**	expression functions
*/

	
/*
**	print function to display contents of the expression
*/

void	expression_print(t_ssl *ssl)
{
	t_expr 	*expr;
	t_list	*tmp;
	t_arg	*arg;
	
	expr = ssl->expr;
	tmp = expr->args->head;
	while (tmp)
	{
		arg = (t_arg*)(tmp->content);
		arg->print(arg);
		tmp = tmp->next;
	}	
}

/*
**	function for adding an argument to the args queue based on msg text
*/

void	expression_add_argument(t_ssl *ssl, char *msg, char *origin)
{
	t_expr	*expr;
	t_arg	*arg;
	
	expr = ssl->expr;
	arg = argument_new(msg, origin, msg);
	ft_enqueue(expr->args, arg, sizeof(t_arg));
}	

/*
**	init functions
*/

/*
**	expression initialization function
*/

void 	ssl_expr_init(t_ssl *ssl)
{
	t_expr	*expr;

	expr = ssl->expr;
	expr->ops = 0;
	expr->args = ft_queuenw(NULL, 0);
	expr->argnw = expression_add_argument;
	expr->print = expression_print;
}

/*
** ssl initialization function accepts an array of strings representing input
** preceeded by the length of the array.
*/

void	ssl_init(t_ssl *ssl)
{ 
	ssl->cmds = g_cmds;
	ssl->read = ssl_cdl_parse;
	ssl->eval = NULL;
	ssl->expr = ft_memalloc(sizeof(t_expr));
	ssl->expr->init = ssl_expr_init;
	ssl->prep = ssl_prep;
}

/*
** right now I need to accept the msg either from stdin, or as a file argument.
** in the spirit of reusability I may want to pass a string to ssl for
** evaluation. But right now that is over engineering. I can easily add that
** functionality later by toggling the funtion pointer during initialization.
** This is my complete skeleton. Now I need to flesh out the individual parts.
*/

int 	main(int argc, char ** argv)
{
	t_ssl	ssl;

	ssl_init(&ssl);
	ssl.read(&ssl, argc, argv);
	ssl.prep(&ssl);
	ssl.eval(&ssl);
	//ssl.output(&ssl);
}
