/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 16:36:00 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/10/04 01:36:20 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_options g_options;

t_uchar	*base64_encode(t_uchar *message, int *len)
{
	int		i;
	t_uchar	*cipher;

	i = 0;
	cipher = (t_uchar *)ft_strnew(4 * (*len / 3 + ((*len % 3) ? 1 : 0)));
	while (i < *len / 3)
	{
		pad_0(cipher + i * 4, message + i * 3);
		i++;
	}
	if (*len % 3 == 2)
		pad_1(cipher + i * 4, message + i * 3);
	else if (*len % 3 == 1)
		pad_2(cipher + i * 4, message + i * 3);
	if (*len)
	{
		cipher = (t_uchar *)ft_strfjoin((char *)cipher, "\n");
		*len = 4 * (*len / 3 + ((*len % 3) ? 1 : 0)) + 1;
	}
	return (cipher);
}

t_uchar	*base64_decode(t_uchar *cipher, int *len)
{
	int		i;
	t_uchar	*message;

	i = 0;
	*len = check_padding(cipher, *len);
	message = (t_uchar *)ft_strnew(3 * (*len / 4) + (*len % 4 - 1));
	while (i < *len / 4)
	{
		message[3 * i + 0] = (revchar(*(cipher + i * 4)) << 2)
		+ ((revchar(*(cipher + i * 4 + 1)) & 0x30) >> 4);
		message[3 * i + 1] = (revchar(*(cipher + i * 4 + 1)) << 4)
		+ (revchar(*(cipher + i * 4 + 2)) >> 2);
		message[3 * i + 2] = (revchar(*(cipher + i * 4 + 2)) << 6)
		+ revchar(*(cipher + i * 4 + 3));
		i++;
	}
	if (*len % 4 > 1)
		message[3 * i + 0] = (revchar(*(cipher + i * 4)) << 2)
		+ ((revchar(*(cipher + i * 4 + 1)) & 0x30) >> 4);
	if (*len % 4 == 3)
		message[3 * i + 1] = (revchar(*(cipher + i * 4 + 1)) << 4)
		+ (revchar(*(cipher + i * 4 + 2)) >> 2);
	*len = 3 * (*len / 4) + (*len % 4 - 1);
	return (message);
}

int		base64(t_uchar **output)
{
	int		len;
	t_uchar	*input;

	input = read_all(g_options.fd_in, &len);
	if (g_options.mode == Encrypt)
		*output = base64_encode(input, &len);
	else
		*output = base64_decode(input, &len);
	return (len);
}
