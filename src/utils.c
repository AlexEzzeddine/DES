/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:30:36 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/28 05:31:07 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_ulong	char_to_hex_digit(char c)
{
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else
		return (c - '0');
}

t_uchar	revchar(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		ch -= 'A';
	else if (ch >= 'a' && ch <= 'z')
		ch = ch - 'a' + 26;
	else if (ch >= '0' && ch <= '9')
		ch = ch - '0' + 52;
	else if (ch == '+')
		ch = 62;
	else if (ch == '/')
		ch = 63;
	else if (ch == '=')
		ch = 0;
	return (ch);
}

t_ulong	convert_hex_to_bits(char *key)
{
	t_ulong	k;
	int		i;

	k = 0;
	i = 0;
	while (i < 16)
	{
		k += (char_to_hex_digit(key[i]) << (4 * (15 - i)));
		i++;
	}
	return (k);
}
