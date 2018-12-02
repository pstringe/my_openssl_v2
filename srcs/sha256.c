/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:20:43 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/28 22:30:13 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	implementation of sha-256 algorithm
*/

void	sha256(t_ssl *ssl, t_arg *arg)
{
	(void)ssl;
	(void)arg;
	ft_printf("function evaluated:%s\n", ssl->expr->cmd.name);
}

