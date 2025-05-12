/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 04:17:09 by olmohame          #+#    #+#             */
/*   Updated: 2024/11/03 13:04:46 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_keyword(char **keywords)
{
	keywords[0] = "NO";
	keywords[1] = "SO";
	keywords[2] = "EA";
	keywords[3] = "WE";
	keywords[4] = "F";
	keywords[5] = "C";
}

int	store_settings(t_all *data, char **line)
{
	int		i;
	char	*err_msg;
	char	*keywords[6];

	init_keyword(keywords);
	i = -1;
	while (++i < 6)
	{
		if (ft_strncmp(*line, keywords[i], 2) == 0)
			return (store_texture(&data->temp_data, line, i, keywords[i]));
		if (ft_strncmp(*line, keywords[i], 1) == 0)
			return (store_color(data, line, i - 4, keywords[i]));
	}
	err_msg = "Error\nFound an unexpected line while reading the settings.\n";
	if (**line == '\0' && ft_strlen(*line) == 0)
	{
		free(*line);
		*line = NULL;
	}
	else
		return (put_error(err_msg, "", EXIT_FAILURE));
	return (0);
}

int	get_direction(char special_char, t_all *data, ssize_t pos_x)
{
	if (data->temp_data.has_start)
		return (put_error("Error\nMultiple starting positions\n", "", 0));
	if (special_char == 'W')
	{
		data->dir.x = -1;
		data->dir.y = 0;
	}
	else if (special_char == 'E')
	{
		data->dir.x = 1;
		data->dir.y = 0;
	}
	else if (special_char == 'N')
	{
		data->dir.x = 0;
		data->dir.y = -1;
	}
	else if (special_char == 'S')
	{
		data->dir.x = 0;
		data->dir.y = 1;
	}
	data->pos_x = 0.5 + pos_x;
	data->pos_y = 0.5 + data->map.y - 1;
	return (1);
}

static int	is_directory(char *path)
{
	ssize_t	nbytes;
	int		fd;
	char	buffer[1];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	nbytes = read(fd, buffer, sizeof(buffer));
	close(fd);
	if (nbytes < 0 && (errno == EISDIR))
	{
		put_error("Error\nThe path is a directory\n", "", 1);
		return (1);
	}
	return (0);
}

int	valid_name(char *str)
{
	char	*file;
	char	*extension;
	int		fd;

	if (is_directory(str))
		return (0);
	fd = open(str, O_RDONLY);
	if (fd > -1)
		close(fd);
	if (fd >= 0)
	{
		if (ft_strrchr(str, '/') == NULL)
			file = str;
		else
			file = ft_strrchr(str, '/') + 1;
		extension = ft_strnstr(file, ".cub", ft_strlen(file));
		if (ft_strlen(file) > 4 && extension && !ft_strcmp(extension, ".cub"))
			return (1);
	}
	if (fd < 0)
		put_error("Error\n", strerror(errno), EXIT_FAILURE);
	else
		put_error("Error\nExpects <filename.cub>\n", "", EXIT_FAILURE);
	return (0);
}
