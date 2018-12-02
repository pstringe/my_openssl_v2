/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expression.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 18:54:27 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/30 09:38:42 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"
	
/*
**	print function to display contents of the expression
*/

void	expression_print(t_ssl *ssl)
{
	t_expr 	*expr;
	t_list	*tmp;
	t_arg	*arg;
	
	expr = ssl->expr;
	tmp = expr->args->head;
	while (tmp)
	{
		arg = (t_arg*)(tmp->content);
		arg->print(arg);
		tmp = tmp->next;
	}	
}

/*
**	function for adding an argument to the args queue based on msg text
*/

void	expression_add_argument(t_ssl *ssl, char *msg, char *origin)
{
	t_expr	*expr;
	t_arg	*arg;
	
	expr = ssl->expr;
	arg = argument_new(ssl, origin, msg);
	ft_enqueue(expr->args, arg, sizeof(t_arg));
}	

/*
**	init functions
*/

/*
**	expression initialization function
*/

void 	ssl_expr_init(t_ssl *ssl)
{
	t_expr	*expr;

	expr = ssl->expr;
	expr->ops = 0;
	expr->args = ft_queuenw(NULL, 0);
	expr->argnw = expression_add_argument;
	expr->print = expression_print;
}

