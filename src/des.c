/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 12:29:48 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/28 05:03:43 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <stdio.h>

extern t_options g_options;

int		des(t_uchar **output)
{
	int		len;
	t_uchar	*input;

	get_key();
	input = read_all(g_options.fd_in);
	if (g_options.use_base64 && g_options.mode == Decrypt)
		input = base64_decode(input);
	len = ft_strlen((char *)input);
	if (len % 8)
		input = (t_uchar *)ft_strrealloc((char *)input, len);
	len = 8 * (len / 8 + (len % 8 ? 1 : 0));
	*output = (t_uchar *)ft_strnew(len);
	if (!ft_strcmp(g_options.cipher, "des")
		|| !ft_strcmp(g_options.cipher, "des-ecb"))
		des_ecb(input, output, create_key_schedule(g_options.key), len);
	else if (!ft_strcmp(g_options.cipher, "des-cbc"))
		des_cbc(input, output, create_key_schedule(g_options.key), len);
	else if (!ft_strcmp(g_options.cipher, "des3"))
		des_3(input, output, create_3_key_schedule(g_options.key), len);
	if (g_options.use_base64 && g_options.mode == Encrypt)
		*output = (t_uchar *)base64_encode(*output, &len);
	return (len);
}

void	des_ecb(t_uchar *message, t_uchar **cipher,
	t_ulong *key_schedule, int len)
{
	t_ulong	m;
	t_ulong	c;
	int		i;

	i = 0;
	while (i * 8 < len)
	{
		m = string_to_long64((t_uchar *)message + 8 * i);
		c = process_block(m, key_schedule, g_options.mode);
		long64_to_string(*cipher + 8 * i, c);
		i++;
	}
}

void	des_cbc(t_uchar *message, t_uchar **cipher,
	t_ulong *key_schedule, int len)
{
	t_ulong	m;
	t_ulong	c;
	t_ulong iv;
	int		i;

	iv = convert_hex_to_bits(g_options.ivec);
	i = 0;
	while (i * 8 < len)
	{
		m = string_to_long64((t_uchar *)message + 8 * i);
		if (g_options.mode == Encrypt)
			m ^= iv;
		c = process_block(m, key_schedule, g_options.mode);
		if (g_options.mode == Decrypt)
			c ^= iv;
		iv = g_options.mode == Encrypt ? c : m;
		long64_to_string(*cipher + 8 * i, c);
		i++;
	}
}

void	des_3(t_uchar *message, t_uchar **cipher,
	t_ulong **key_schedules, int len)
{
	t_ulong	m;
	t_ulong	c;
	t_ulong iv;
	int		i;

	iv = convert_hex_to_bits(g_options.ivec);
	i = 0;
	while (i * 8 < len)
	{
		m = string_to_long64((t_uchar *)message + 8 * i);
		if (g_options.mode == Encrypt)
			m ^= iv;
		c = process_block(m, key_schedules[0], g_options.mode);
		m = process_block(c, key_schedules[1], !g_options.mode);
		c = process_block(m, key_schedules[2], g_options.mode);
		if (g_options.mode == Decrypt)
			c ^= iv;
		iv = g_options.mode == Encrypt ? c : m;
		long64_to_string(*cipher + 8 * i, c);
		i++;
	}
}
