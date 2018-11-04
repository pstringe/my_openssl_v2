/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 11:39:49 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/03 20:43:50 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_openssl.h"

t_queue		*ft_queuenw(void *n, size_t size)
{
	t_queue	*q;
	t_list	*tmp;

	q = (t_queue*)ft_memalloc(sizeof(t_queue));
	if (!n || !size)
	{
		q->tail = NULL;
		q->head = NULL;
	}
	else
	{
		tmp = ft_lstnew(n, size);
		q->tail = tmp;
		q->head = tmp;
	}
	return (q);
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

void	md5(t_md5 *state, t_expr *expr)
{
}

/*
**	implementation of sha-256 algorithm
*/

void	sha256(t_sha256 *state, t_expr *expr)
{
}


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
		expr->argnw(&expr, "file", msg);
}

/*
**	command line parse must first check for msg txt in stdin and then check for
**	file/stringarguments. For the latter. We will first attempt to see if the
**	string is a file. If yes we will add its contents to our msg_text list. 
**	Otherwise, we will add the string itself
*/


void	ssl_cdl_parse(t_ssl *ssl, int argc, char **argv)
{
	int	i;
	int	j;

	get_stdin(ssl);
	
	/*Just a test to make sure the msg is being enqueued properly*/
	ssl->expr->print(&ssl->expr);
	/*end of test*/

	i = -1;
	while (ssl->cmds[++i].name)
		if (!ft_strncmp(ssl->cmds[i].name, argv[1], ft_strlen(ssl->cmds[i].name)))
			ft_memcpy((void*)&(ssl->expr->cmd), (const void*)&(ssl->cmds[i]), sizeof(t_cmd));

	/*just a test to verify command parsing works properly*/
	ft_printf("The command is: %s\n", ssl->expr->cmd.name);
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
	
	ft_printf("arg origin: %s", arg->origin);
	i = 0;
	l = ft_strlen(arg->msg);
	while (i < l)
	{
		ft_printf("%.80s\n", arg->msg + i);
		i += 80;
	}
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
**	expression initialization function
*/

void 	ssl_expr_init(t_ssl *ssl)
{
	t_expr	*expr;

	expr = ssl->expr;
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
	ssl->eval = NULL;					/*this will be determined based on 
										  the value of the command after
										  parsing */
	ssl->expr = ft_memalloc(sizeof(t_expr));
	ssl->expr->init = ssl_expr_init;
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
	//ssl.eval(&ssl);
	//ssl.output(&ssl);
}
