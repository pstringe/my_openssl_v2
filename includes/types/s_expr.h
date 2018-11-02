/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_expr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:37:03 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/31 18:41:36 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_EXPR_H
# define S_EXPR_H
# include "s_arg.h"
# include "s_cmd.h"

typedef struct 	s_expr
{
	t_queue		*args;
	t_cmd		*cmd;
	int			ops;
}				t_expr;
#endif
