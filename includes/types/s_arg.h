/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_arg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:40:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/03 15:03:01 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ARG_H
# define S_ARG_H

typedef struct	s_arg
{
	char	*origin;
	char 	*msg;
	t_queue *blocks;
	int32_t	hash[4];

	void	(*print)(struct s_arg*);
}				t_arg;
#endif
