/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_expr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:37:03 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/02 13:52:22 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_EXPR_H
# define S_EXPR_H
# include "s_arg.h"
# include "s_cmd.h"
# include "s_ssl.h"

typedef struct 	s_expr
{
	t_queue		*args;
	t_cmd		*cmd;
	int			ops;

	void		(*argnw)(struct s_expr*, char*, char*);
	void		(*argmv)(struct s_expr*, struct s_arg*);
	void 		(*print)(struct s_expr*);
	void 		(*init)(struct s_ssl*);
}				t_expr;
#endif
