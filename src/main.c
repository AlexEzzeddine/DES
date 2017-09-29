/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 03:06:21 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/09/29 02:43:32 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_options g_options = {NULL, Encrypt, 0, 1, 0, NULL, NULL};

int		main(int argc, char **argv)
{
	t_uchar	*output;
	int		len;

	get_options(argc, argv);
	if (!ft_strcmp(g_options.cipher, "base64"))
		len = base64(&output);
	else
		len = des(&output);
	write(g_options.fd_out, output, len);
	close(g_options.fd_out);
	return (0);
}
