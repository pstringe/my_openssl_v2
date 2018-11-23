/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:25:09 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/22 16:13:08 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

static void	append_length(char *msg, uint64_t pl, uint64_t length)
{

	length *= 8; 					//get the length in bits
	msg[pl - 1] = length;
	msg[pl - 2] = length >> 8;
	msg[pl - 3] = length >> 16;
	msg[pl - 4] = length >> 24;
	msg[pl - 5] = length >> 32;
	msg[pl - 6] = length >> 40;
	msg[pl - 7] = length >> 48;
	msg[pl - 8] = length >> 56;
}

void			arg_pad(t_arg *arg)
{
	uint64_t 	l;		//length padding buff text in bytes
	uint64_t	d;		//difference between the length of the msg text and the msg text
	uint64_t	i;
	unsigned char		*pad;

	//get length
	d = 0;
	l = arg->length - 1;
	while (((++l * 8) % 512)/* && d < 8*/)
		 d++;

	//allocate new string
	pad = ft_strnew(l);
	
	//set first bit
	pad[arg->length] = 128;

	//cpy msg text
	ft_memcpy(pad, arg->msg, arg->length);

	//append length bits
	append_length(pad, l, arg->length);

	//free old string and set the padded one
	free(arg->msg);
	arg->msg = pad;
	arg->length = l;
}

