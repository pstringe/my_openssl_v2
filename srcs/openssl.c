/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 11:39:49 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/08 14:18:21 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	global variable used to initialize command dispatch table 
*/

t_cmd	g_cmds[3] = {
	{"md5", md5},
	{"sha256", sha256},
	{NULL, NULL}
};

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
	t_queue *args;
	t_arg	*arg;

	ssl_init(&ssl);
	ssl.read(&ssl, argc, argv);
	ssl.prep(&ssl);

	args = ssl.expr->args;
	while ((arg = ft_dequeue(args)))
		ssl.eval(&ssl, arg);
	//ssl.output(&ssl);
}
