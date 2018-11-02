/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 11:39:49 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/02 09:23:35 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_openssl.h"

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
**	command line parse must first check for msg txt in stdin and then check for
**	file/stringarguments. For the latter. We will first attempt to see if the
**	string is a file. If yes we will add its contents to our msg_text list. 
**	Otherwise, we will add the string itself
*/


void	ssl_cdl_parse(t_ssl *ssl, int argc, char **argv)
{
	/*
	 t_expr	*expr;
	t_queue *messages;
	
	expr = ssl->expression;
	messages = expr->message_queue;
	//check of stdin is open and read contents into queue
	if (get_next_line(0, *line))
		ft_enqueue(&messages,);
	*/
}


/*
**	global variable used to initialize command dispatch table 
*/

t_cmd	g_cmds[3] = {
	{"md5", md5},
	{"sha256", sha256},
	NULL
};

/*
** ssl initialization function accepts an array of strings representing input
** preceeded by the length of the array.
*/

void	ssl_init(t_ssl *ssl)
{ 
	ssl->cmds = g_cmds;
	ssl->expr = NULL;
	ssl->read = ssl_cdl_parse;
	ssl->eval = NULL;					/*this will be determined based on 
										  the value of the command after
										  parsing */
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
	//ssl.read(&ssl, int argc, char **argv);
	//ssl.eval(&ssl);
	//ssl.output(&ssl);
}
