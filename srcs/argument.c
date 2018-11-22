/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:56:18 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/19 09:33:25 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	a function the print the argument, In this case I must pass the 
**	specific argument pointer since there may be many args per ssl instance.
*/

void	argument_print(t_arg *arg)
{
	int i;
	int	l;
	
	ft_printf("arg origin:\t%s\n", arg->origin);
	ft_printf("arg message:\t%s\n", arg->msg);
	
	/*
	i = 0;
	l = ft_strlen(arg->msg);
	while (i < l)
	{
		ft_printf("%.80s\n", arg->msg + i);
		i += 80;
	}
	*/
}

/*
**	function for allocating a new argument and initializing it with a value
*/

t_arg	*argument_new(t_ssl *ssl, char *msg, char *origin)
{
	t_arg	*arg;
	
	arg = ft_memalloc(sizeof(t_arg));
	arg->origin = ft_strdup(origin);
	arg->msg = ft_strdup(msg);
	arg->length = ft_strlen(msg);
	arg->prep = arg_prep;
	arg->prepped = 0;
	arg->block = arg_block;
	arg->print = argument_print; 
	return (arg);
}

