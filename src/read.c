/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aezzeddi <aezzeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 10:42:46 by aezzeddi          #+#    #+#             */
/*   Updated: 2017/10/04 02:02:03 by aezzeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

extern t_options g_options;

t_uchar	*read_all(int fd, int *len)
{
	char	*result;
	char	*old;
	char	*buf;
	int		n;
	int		count;

	buf = ft_strnew(8);
	result = NULL;
	count = 0;
	while ((n = read(fd, buf, 8)) > 0)
	{
		old = result;
		result = ft_strnew(count + n + 1);
		ft_memcpy(result, old, count);
		ft_memcpy(result + count, buf, n);
		count += n;
		free(old);
		ft_bzero(buf, 8);
	}
	*len = count;
	if (n < 0)
		write(2, strerror(errno), ft_strlen(strerror(errno)));
	return (t_uchar *)result;
}

void	get_command(char **argv, int argc)
{
	char	*command;

	if (argc == 1)
		usage();
	command = argv[1];
	if (!ft_strcmp(command, "base64")
		|| !ft_strcmp(command, "des")
		|| !ft_strcmp(command, "des-ecb")
		|| !ft_strcmp(command, "des-cbc")
		|| !ft_strcmp(command, "des3"))
		g_options.cipher = command;
	else
		command_error(command);
}

void	get_options(int argc, char **argv)
{
	int i;

	get_command(argv, argc);
	i = 2;
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-e"))
			g_options.mode = Encrypt;
		else if (!ft_strcmp(argv[i], "-d"))
			g_options.mode = Decrypt;
		else if (!ft_strcmp(argv[i], "-a"))
			g_options.use_base64 = 1;
		else if (!ft_strcmp(argv[i], "-i"))
			g_options.fd_in = open(argv[++i], O_RDONLY);
		else if (!ft_strcmp(argv[i], "-o"))
			g_options.fd_out = open(argv[++i], O_WRONLY | O_CREAT, 0666);
		else if (!ft_strcmp(argv[i], "-k"))
			g_options.key = argv[++i];
		else if (!ft_strcmp(argv[i], "-v"))
			g_options.ivec = argv[++i];
		else
			usage();
		i++;
	}
}

void	get_ivec(void)
{
	if (!ft_strcmp(g_options.cipher, "des-cbc")
		|| !ft_strcmp(g_options.cipher, "des3"))
	{
		if (!(g_options.ivec))
		{
			g_options.ivec = ft_strnew(16);
			readpassphrase("enter initial vector: ",
				g_options.ivec, 17, RPP_ECHO_ON);
		}
		g_options.ivec = normalize_key(g_options.ivec, 16);
	}
}

void	get_key(void)
{
	int key_size;

	key_size = 16;
	if (!ft_strcmp(g_options.cipher, "des3"))
		key_size = 48;
	if (!(g_options.key))
	{
		g_options.key = ft_strnew(key_size);
		readpassphrase("enter des key in hex: ",
			g_options.key, key_size + 1, RPP_ECHO_ON);
	}
	g_options.key = normalize_key(g_options.key, key_size);
}
