/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:19:39 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/19 12:24:19 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
** implementation of message digest algorithm 
*/

void	md5(t_ssl *ssl)
{
	ft_printf("function evaluated:%s\n", ssl->expr->cmd.name);
}
