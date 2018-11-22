/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:25:09 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/22 15:20:59 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

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

