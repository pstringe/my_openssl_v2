/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 19:06:16 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/19 09:33:30 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

/*
**	given a postion in a string, initializes a new block and copies 64 bytes
**	that position or until a null byte is encountered, the number of copied 
**	bytes will also be assigned to block->length.
**	We also increment the position of the given string here. We need to pass in
** 	a new pointer to avoid a memory leak.
*/

t_block 	*block_new(char **pos, size_t count)
{
	t_block *block;
	int		l;

	block = NULL;
	if (**pos)
	{
		block = ft_memalloc(sizeof(t_block));
		block->text = ft_strnew(64);
		ft_memcpy(block->text, *pos, (l = ft_strlen(*pos)) < 64 ? l : 64);
		*pos += l < 64 ? l : 64;
		block->length = l < 64 ? l : 64;
		block->print = block_print;
		block->count = count;
	}
	return (block);
}
