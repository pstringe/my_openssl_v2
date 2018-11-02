/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_cmd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 16:27:37 by pstringe          #+#    #+#             */
/*   Updated: 2018/10/31 18:41:32 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_CMD
# define S_CMD
# include "s_expr.h"

typedef struct	s_cmd
{
	char		*name;
	void 		(*func)(struct s_expr *expr);
}				t_cmd;

#endif
