/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:24:09 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/02 13:32:14 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPR_H
# define EXPR_H
# include "types/s_ssl.h"

void 	ssl_expr_init(t_ssl *ssl);
void	expression_print(t_ssl *ssl);
void	expression_add_argument(t_ssl *ssl, char *msg, char *origin);
#endif
