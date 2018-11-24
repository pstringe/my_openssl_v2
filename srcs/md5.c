/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:19:39 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/23 16:58:35 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
** implementation of message digest algorithm 
*/

void	md5(t_ssl *ssl)
{
	uint32_t	a0 = 0x67452301;
	uint32_t	b0 = 0xefcdab89;
	uint32_t 	c0 = 0x98badcfe;
	uint32_t	d0 = 0x10325476;

	
	ft_printf("function evaluated:%s\n", ssl->expr->cmd.name);
}
