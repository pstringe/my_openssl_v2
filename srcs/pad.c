/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:25:09 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/28 22:28:55 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

static void	append_length(unsigned char *msg, uint64_t pl, uint64_t length)
{
	int	i;

	length *= 8;
	i = -1;
	while (++i <= 8)	//get the length in bits
		msg[pl - (i + 1)] = length >> (i * 8);
}

void			arg_pad(t_arg *arg)
{
	uint64_t 			l;
	unsigned char		*pad;

	l = arg->length - 1;
	while (((++l * 8) % 512));
	pad = (unsigned char*)ft_strnew(l);
	pad[arg->length] = 128;
	ft_memcpy(pad, arg->msg, arg->length);
	append_length(pad, l, arg->length);
	free(arg->msg);
	arg->msg = pad;
	arg->length = l;
}

