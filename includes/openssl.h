/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openssl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstringe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 12:22:28 by pstringe          #+#    #+#             */
/*   Updated: 2018/12/01 21:02:08 by pstringe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENSSL_H
# define FT_OPENSSL_H
# define OP_P			2
# define OP_Q			4
# define OP_R			8
# define OP_S			16
# include <assert.h>
# include "libft/libft.h"
//# include "chunk.h"
//# include "ssl.h"
//# include "md5.h"
//# include "sha256.h"

/*
**	forward declarations
*/

typedef	struct	s_expr t_expr;
typedef struct	s_cmd	t_cmd;
typedef struct	s_arg	t_arg;
typedef struct	s_ssl	t_ssl;
typedef struct	s_chunk	t_chunk;
typedef struct	s_md5	t_md5;


typedef struct	s_cmd
{
	char		*name;
	void 		(*func)(t_ssl*, t_arg*);
}				t_cmd;

typedef struct 	s_expr
{
	t_queue		*args;
	t_cmd		cmd;
	int			ops;

	void		(*argnw)(struct s_ssl*, char*, char*);
	void 		(*print)(struct s_ssl*);
	void		(*argmv)(struct s_expr*, struct s_arg*);
	void 		(*init)(struct s_ssl*);
}				t_expr;


typedef struct	s_ssl
{
	t_expr		*expr;
	t_cmd		*cmds;
	void		(*read)(struct s_ssl*, int, char**);
	void		(*prep)(struct s_ssl*);
	void		(*eval)(struct s_ssl*, t_arg*);
	void		(*output)(struct s_ssl*);
}				t_ssl;

typedef struct	s_md5
{
	uint32_t	*s;		//shift amounts
	uint32_t	*k;		//constants

	//initial resigter constants
	int			a0;
	int			b0;
	int			c0;
	int			d0;

	//registers
	int			a;
	int			b;
	int			c;
	int			d;

	//result of compression funtion
	uint32_t	f;

	//message blocks
	uint32_t	m[16];
	uint32_t	g;	

	void		(*block)(t_md5*, t_chunk *c);
}				t_md5;

typedef struct	s_arg
{
	int			prepped;
	char		*origin;
	unsigned char		*msg;
	uint64_t	length;
	t_queue 	*chunks;
	uint32_t	md5_hash[4];

	void		(*prep)(struct s_ssl*, struct s_arg*);
	void		(*chunk)(struct s_arg*);
	void		(*print)(struct s_arg*);
}				t_arg;

typedef struct	s_chunk
{
	size_t	count;
	size_t 	length;
	char 	*text;
	void	(*print)(struct s_chunk*, char*);
}				t_chunk;

typedef struct	s_sha256
{
}				t_sha256;

/*
**	argument functions
*/

void			argument_print(t_arg *arg);
t_arg			*argument_new(t_ssl *ssl, char *msg, char *origin);

/*
**	block functions
*/

t_chunk 		*chunk_new(unsigned char **pos, size_t count);

/*
**	expression functions
*/

void			expression_print(t_ssl *ssl);
void			expression_add_argument(t_ssl *ssl, char *msg, char *origin);
void 			ssl_expr_init(t_ssl *ssl);

/*
**	padding functions
*/

unsigned char	*itos(uint64_t n);
void			arg_pad(t_arg *arg);

/*
**	parsing functions		
*/

void			get_stdin(t_ssl *ssl);
void			get_cmd(t_ssl *ssl, char **argv);
int 			get_ops(t_ssl *ssl, char **argv, int argc);
void			get_args(t_ssl *ssl, int idx, int argc, char **argv);
void			ssl_cdl_parse(t_ssl *ssl, int argc, char **argv);

/*
**	prep functions
*/

void			arg_chunk(t_arg *arg);
void			arg_prep(t_ssl *ssl, t_arg *arg);
void 			ssl_prep(t_ssl *ssl);

/*
**	md5
*/

void			md5(t_ssl *ssl, t_arg *arg);

/*
**	sha-256
*/

void			sha256(t_ssl *ssl, t_arg *arg);

/*
**	utility functions
*/

void			chunk_inspect(t_chunk *chunk);
void 			chunk_print(t_chunk *chunk, char *base);
#endif
