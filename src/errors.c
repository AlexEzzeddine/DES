/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 05:05:40 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/28 05:06:08 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	usage(void)
{
	ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	exit(0);
}

void	list_standard_commands(void)
{
	ft_putstr("Standard commands:\n");
	ft_putstr("\n");
}

void	list_digest_commands(void)
{
	ft_putstr("Message Digest commands:\n");
	ft_putstr("\n");
}

void	list_cipher_commands(void)
{
	ft_putstr("Cipher commands:\n");
	ft_putstr("base64\n");
	ft_putstr("des\n");
	ft_putstr("des-ecb\n");
	ft_putstr("des-cbc\n");
	ft_putstr("des3\n");
}

void	command_error(char *command)
{
	ft_putstr("ft_ssl: Error: '");
	ft_putstr(command);
	ft_putstr("' is an invalid command.\n\n");
	list_standard_commands();
	list_digest_commands();
	list_cipher_commands();
	exit(0);
}
