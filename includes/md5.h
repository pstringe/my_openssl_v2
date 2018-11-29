/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:13:51 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/25 17:36:07 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H
# include "types/s_ssl.h"
# include "types/s_md5.h"
# include "types/s_expr.h"

void	md5(t_ssl *ssl, t_arg *arg);
#endif
