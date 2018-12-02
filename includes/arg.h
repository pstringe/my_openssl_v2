/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:09:20 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/02 13:16:34 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H
# include "types/s_arg"
# include "types/s_expr"

t_arg	*argument_new(t_ssl *ssl, char *msg, char *origin);
void	argument_print(t_arg *arg);
#endif
