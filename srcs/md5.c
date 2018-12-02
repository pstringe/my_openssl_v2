/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:19:39 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/01 20:03:56 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "openssl.h"

# define F(b, c, d)		(b & c) | (~b & d)
# define G(b, c, d)		(b & d) | (c & ~d)
# define H(b, c, d)		b ^ c ^ d
# define I(b, c, d)		c ^ (b | ~d)

void	init(t_md5 *m)
{
	m->K = (uint32_t [64])
	{	
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 
	};
	
	/* variable constants */
	m->a0 = 0x67452301;
	m->b0 = 0xefcdab89;
	m->c0 = 0x98badcfe;
	m->d0 = 0x10325476;
}

/*
**	break chunk into 16 32 bit blocks
*/

void	block(t_md5 *m, t_chunk *c)
{
	int	i;	//position in chunk text
	int	j;	//position in block arrray
	int	k;	//shift ammount

	i = -1;
	j = -1;
	while (++j < 16)
	{
		k = 4;
		while (--k >= 0)
			m->m[j] |= (uint32_t)c->text[++i] << k; 
	}
}

/*
** implementation of message digest algorithm 
*/

void	md5(t_ssl *ssl, t_arg *arg)
{
	(void)		ssl;
	t_chunk		*chunk;
	t_md5		m;
	int			i;
	
	//512 chunk loop
	while ((chunk = ft_dequeue(arg->blocks)))
	{
		//break chunk into  16 32 bit words
		m.block(&m, chunk);

		//initialize current chunk's hash value
		m.a = m.a0;
		m.b = m.b0;
		m.c = m.c0;
		m.d = m.d0;
		
		//Main Loop
		i = -1;
		while (++i < 64)
		{
			if (i < 16)
			{
				m.f = F(m.b, m.c, m.d);
				m.g = i;
			}
			else if (i < 32)
			{
				m.f = G(m.b, m.c, m.d);
				m.g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				m.f = H(m.b, m.c, m.d);
				m.g = (3 * i + 5) % 16;
			}
			else
			{
				m.f = G(m.b, m.c, m.d); 
				m.g = (7 * i) % 16;
			}

			m.f += m.f + m.a + m.k[i] + m[m.g];
			m.a = m.d;
			m.d = m.c;
			m.c = m.b;
			m.b = m.f << m.s[i];
		}
		m.a0 += m.a;
		m.b0 += m.b;
		m.c0 += m.c;
		m.d0 += m.d;

		ft_memdel((void**)&chunk);	
	}

	//append values to digest in little-endian order
	arg->md5_hash[0] = m.a0;
	arg->md5_hash[1] = m.a1;
	arg->md5_hash[2] = m.a2;
	arg->md5_hash[3] = m.a3;

	ft_printf("md5: %s %x%x%x%x\n", ssl->expr->cmd.name, m.a0, m.a1, m.a2, m.a3);
}
