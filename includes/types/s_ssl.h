/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_ssl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 12:26:08 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/05 14:23:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_SSL_H
# define S_SSL_H
# include "s_expr.h"
# include "s_cmd.h"

typedef struct	s_ssl
{
	t_expr		*expr;	
	t_cmd		*cmds;
	void		(*read)(struct s_ssl*, int, char**);
	void		(*prep)(struct s_ssl*);
	void		(*eval)(struct s_ssl*);
	void		(*output)(struct s_ssl*);
}				t_ssl;

#endif
