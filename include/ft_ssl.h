/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 03:07:03 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/28 21:25:48 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <libft.h>
# include <fcntl.h>
# include <readpassphrase.h>
# include <errno.h>

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;

typedef enum	e_mode
{
	Encrypt,
	Decrypt
}				t_mode;

typedef struct	s_options
{
	char	*cipher;
	t_mode	mode;
	int		fd_in;
	int		fd_out;
	int		use_base64;
	char	*key;
	char	*ivec;
}				t_options;

t_uchar			*read_all(int fd);
void			get_options(int argc, char **argv);
t_ulong			convert_hex_to_bits(char *key);
t_uchar			revchar(char ch);
t_ulong			string_to_long64(t_uchar *str);
void			long64_to_string(t_uchar *str, t_ulong n);
t_ulong			permute(t_ulong old_block,
	const int *permutation_map, int size);
int				get_bit(t_ulong buf, t_ulong bit);
void			set_bit(t_ulong *buf, t_ulong bit);
int				check_padding(t_uchar *cipher, int len);

void			pad_0(t_uchar *cipher, t_uchar *message);
void			pad_1(t_uchar *cipher, t_uchar *message);
void			pad_2(t_uchar *cipher, t_uchar *message);
t_uchar			*base64_encode(t_uchar *message, int *len);
t_uchar			*base64_decode(t_uchar *cipher, int *len);
int				base64(t_uchar **output);

void			get_ivec(void);
void			get_key(void);
char			*normalize_key(char *old_key, int key_size);
t_ulong			rotate_sub_key(t_ulong key, int shift);
t_ulong			*create_key_schedule(char *key);
t_ulong			**create_3_key_schedule(char *key_192);

t_ulong			process_block(t_ulong m, t_ulong *keys, t_mode mode);

int				des(t_uchar **output);
void			des_ecb(t_uchar *message, t_uchar **cipher,
	t_ulong *key_schedule, int len);
void			des_cbc(t_uchar *message, t_uchar **cipher,
	t_ulong *key_schedule, int len);
void			des_3(t_uchar *message, t_uchar **cipher,
	t_ulong **key_schedules, int len);

void			usage(void);
void			command_error(char *command);

#endif
