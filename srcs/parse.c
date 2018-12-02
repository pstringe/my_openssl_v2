/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:58:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/01 21:01:51 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	function to retrieve data from stdin
*/

void	get_stdin(t_ssl *ssl)
{
	char	*msg;
	t_expr	*expr;
	t_arg	*args;

	(void)args;
	expr = ssl->expr;
	expr->init(ssl);
	msg = NULL;
	if (get_next_line(0, &msg) >= 0)
		expr->argnw(ssl, "stdin", msg);
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
		{
			ft_memcpy(&(ssl->expr->cmd), &(ssl->cmds[i]), sizeof(t_cmd));
			ssl->eval = ssl->cmds[i].func;
		}
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
		ssl->expr->argnw(ssl, fd > 0 ? "file" : "arg", msg);
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
	ssl->expr->print(ssl);
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
	ssl->expr->print(ssl);
	/*end of test*/
}
