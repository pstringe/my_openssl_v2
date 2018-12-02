/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:17:27 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/01 21:01:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	break the msg text into 64 byte (512bit) blocks
*/

void	arg_chunk(t_arg *arg)
{
	int				i;
	unsigned char 	*msg;
	t_chunk	*chunk;

	arg->chunks = ft_queuenw(NULL, 0);
	msg = arg->msg;		/*the new block function will increment this position, 
						we copy the pointer to maintain the original position 
						thus avoiding a leak*/
	i = -1;
	while ((chunk = chunk_new(&msg, ++i)))
	{
		/* just a test to make sure the blocks are bing formed correctly */
		//chunk->print(chunk, "inspect");
		/*end of test*/

		ft_enqueue(arg->chunks, chunk, sizeof(t_chunk));
		free(chunk);
	}
}

void	arg_prep(t_ssl *ssl, t_arg *arg)
{
	(void)ssl;
	arg_pad(arg);
	arg->chunk(arg);
	arg->prepped = 1;
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
		ft_enqueue(args, arg, sizeof(t_arg));
		/*A test to make sure execution reaches this point every time*/
		
		free(arg);
	}
}
