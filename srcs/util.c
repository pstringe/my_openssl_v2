/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:15:18 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/22 14:31:02 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	a function to inspect a block's bytes
*/

void	block_inspect(t_block *block)
{
	int i;
	int j;
	int k;
	int r;

	ft_putendl("-------------------------------------------------------");
	i = -1;
	k = -1;
	i = -1;
	while (++i < 8)
	{
		r = k;
		j = -1;
		while (++j < 8)
			ft_printf("%-4c | ", block->text[++k]);
		ft_putchar('\n');
		k = r;
		j = -1;
		while (++j < 8)
			ft_printf("%#4hx | ", block->text[++k]);
		ft_putchar('\n');
		while (++j < 64)
			ft_putchar('-');
		ft_putchar('\n');
	}
}

/*
**	a function to display blocks as they are enqueued or dequeued for testing purposes
*/

void 	block_print(t_block *block, char *base)
{
	ft_printf("block: %d\n", block->count);
	if (!ft_strncmp(base, "ascii", 5))
		ft_printf("block:\n%s\n", block->text);
	else if (!ft_strncmp(base, "inspect", 3))
		block_inspect(block);
	ft_printf("\n");
}

