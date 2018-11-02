/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:01:38 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/31 16:09:57 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
# define SSL_H
# include "types/s_ssl.h"

void	ssl_init(t_ssl *ssl);
void	ssl_commandline_parse(t_ssl *ssl, int argc, char **argv);

#endif
