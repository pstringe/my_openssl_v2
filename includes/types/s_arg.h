/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_arg.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:40:26 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/06 18:12:53 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_ARG_H
# define S_ARG_H
# include "s_ssl.h"
# include "s_arg.h"
typedef struct	s_arg
{ 
	int			*prepped;	
	char		*origin;
	char		*msg;
	uint64_t	length;
	t_queue 	*blocks;
	int32_t		hash[4];
	
	void		(*prep)(struct s_ssl*, struct s_arg*);
	void		(*block)(struct t_arg*);
	void		(*print)(struct s_arg*);
}				t_arg;
#endif
