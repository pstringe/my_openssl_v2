/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 19:06:16 by pstringe          #+#    #+#             */
/*   Updated: 2018/11/28 22:36:52 by pstringe         ###   ########.fr       */
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

t_chunk 	*chunk_new(unsigned char **pos, size_t count)
{
	t_chunk *chunk;
	int		l;

	chunk = NULL;
	if (**pos)
	{
		chunk = ft_memalloc(sizeof(t_chunk));
		chunk->text = ft_strnew(64);
		ft_memcpy(chunk->text, *pos, (l = ft_strlen((const char*)*pos)) < 64 ? l : 64);
		*pos += l < 64 ? l : 64;
		chunk->length = l < 64 ? l : 64;
		chunk->print = chunk_print;
		chunk->count = count;
	}
	return (chunk);
}
