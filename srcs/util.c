/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:15:18 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/30 10:46:07 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	a function to inspect a block's bytes
*/

void	chunk_inspect(t_chunk *chunk)
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
			ft_printf("%-4c | ", chunk->text[++k]);
		ft_putchar('\n');
		k = r;
		j = -1;
		while (++j < 8)
			ft_printf("%#4hx | ", chunk->text[++k]);
		ft_putchar('\n');
		while (++j < 64)
			ft_putchar('-');
		ft_putchar('\n');
	}
}

/*
**	a function to display blocks as they are enqueued or dequeued for testing purposes
*/

void 	chunk_print(t_chunk *chunk, char *base)
{
	ft_printf("block: %d\n", chunk->count);
	if (!ft_strncmp(base, "ascii", 5))
		ft_printf("block:\n%s\n", chunk->text);
	else if (!ft_strncmp(base, "inspect", 3))
		chunk_inspect(chunk);
	ft_printf("\n");
}

