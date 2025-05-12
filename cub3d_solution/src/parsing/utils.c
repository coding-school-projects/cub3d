/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 02:14:58 by olmohame          #+#    #+#             */
/*   Updated: 2024/11/07 13:24:26 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cub_get_next_line(int fd, int action)
{
	char	*line;

	if (fd < 0)
		return (NULL);
	line = get_next_line(fd, 1 * action);
	if (!line)
		close(fd);
	return (line);
}

int	put_error(char *error_msg, char *details, int exit_code)
{
	if (write(2, error_msg, ft_strlen(error_msg)) == -1)
		return (-1);
	if (ft_strlen(details) != 0)
	{
		if (write(2, details, ft_strlen(details)) == -1)
			return (-1);
		if (write(2, "\n", ft_strlen("\n")) == -1)
			return (-1);
	}
	return (exit_code);
}

int	contains_spaces(const char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}

size_t	ft_strclen(const char *str, char cond)
{
	size_t	str_len;

	str_len = 0;
	while (str[str_len] != cond && str[str_len])
		str_len++;
	return (str_len);
}

size_t	ft_count_words(char const *str, char sep)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (!*str)
			break ;
		str += ft_strclen(str, sep);
		count++;
	}
	return (count);
}
