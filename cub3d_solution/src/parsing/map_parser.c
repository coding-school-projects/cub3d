/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 02:39:13 by olmohame          #+#    #+#             */
/*   Updated: 2024/11/03 13:03:20 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**resize_list(t_all *data, char *line, ssize_t *capacity)
{
	ssize_t	i;
	ssize_t	new_capacity;
	char	**new_list;

	new_capacity = (*capacity) * 2;
	new_list = ft_calloc(new_capacity, sizeof(char *));
	if (new_list == NULL)
	{
		cub_get_next_line(data->temp_data.fd, STOP_READING);
		free(line);
		del_data(data);
		put_error("Error\nMalloc failed\n", "", 0);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *capacity)
	{
		new_list[i] = data->map.tab[i];
		i++;
	}
	free(data->map.tab);
	*capacity = new_capacity;
	data->map.tab = new_list;
	return (new_list);
}

static int	is_valid_line(char *line, t_all *data)
{
	ssize_t	i;
	char	*err_msg;

	i = 0;
	err_msg = "Error\nFound an empty line while parsing the map\n";
	if (ft_strlen(line) == 0)
		return (put_error(err_msg, "", 0));
	err_msg = "Error\nFound invalid character in the map\n";
	while (line[i])
	{
		if (!ft_strchr(VALID_CHARS, line[i]) && !ft_isspace(line[i]))
			return (put_error(err_msg, "", 0));
		if (ft_strchr(PLAYER_ORIENTATION_CHARS, line[i]))
		{
			if (!get_direction(line[i], data, i))
				return (0);
			data->temp_data.has_start = 1;
		}
		i++;
	}
	if (data->map.x < i)
		data->map.x = i;
	return (1);
}

static void	pad_strings(t_all *data, char **list, int max_length)
{
	int		i;
	int		length;
	char	*padded_str;

	i = 0;
	while (i < data->map.y)
	{
		length = ft_strlen(list[i]);
		if (length < max_length)
		{
			padded_str = (char *)malloc((max_length + 1) * sizeof(char));
			if (padded_str == NULL)
			{
				del_data(data);
				exit(put_error("Error\nMalloc failed\n", "", EXIT_FAILURE));
			}
			ft_strcpy(padded_str, list[i]);
			ft_memset(padded_str + length, ' ', max_length - length);
			padded_str[max_length] = '\0';
			free(list[i]);
			list[i] = padded_str;
		}
		i++;
	}
}

static int	process_map(t_all *data, char **list, int fd, char *line)
{
	ssize_t	capacity;

	capacity = LIST_INITIAL_SIZE;
	while (line)
	{
		if (data->map.y + 1 >= capacity)
			list = resize_list(data, line, &capacity);
		list[data->map.y++] = line;
		if (!is_valid_line(line, data))
		{
			cub_get_next_line(fd, STOP_READING);
			return (1);
		}
		line = cub_get_next_line(fd, CLEAN_LINE);
	}
	if (errno)
		return (put_error("Error\n", strerror(errno), EXIT_FAILURE));
	if (!data->temp_data.has_start)
		return (put_error("Error\nCouldn't find a starting position\n", "", 1));
	return (0);
}

int	parse_map(t_all *data, int fd)
{
	char	*line;

	line = cub_get_next_line(fd, CLEAN_LINE);
	while (line && line[0] == '\0')
	{
		free(line);
		line = cub_get_next_line(fd, CLEAN_LINE);
	}
	if (line == NULL && errno != 0)
		return (put_error("Error\nMissing the map\n", "", EXIT_FAILURE));
	if (line == NULL && errno)
		return (put_error("Error\n", strerror(errno), EXIT_FAILURE));
	data->map.x = ft_strlen(line);
	if (process_map(data, data->map.tab, fd, line))
		return (EXIT_FAILURE);
	pad_strings(data, data->map.tab, data->map.x);
	data->temp_data.successful = map_contained(data);
	return (0);
}
