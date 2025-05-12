/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:54:11 by olmohame          #+#    #+#             */
/*   Updated: 2024/11/03 13:04:25 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	validate_and_clean(char **input_string, const char *keyword)
{
	char	*p;
	int		keyword_len;
	char	*err_msg;

	p = *input_string;
	err_msg = "Error\nInvalid syntax when parsing the settings\n";
	keyword_len = ft_strlen(keyword);
	if (ft_strncmp(p, keyword, keyword_len) != 0 || !ft_isspace(p[keyword_len]))
		return (put_error(err_msg, "", 1));
	err_msg = "Error\nThe setting doesn't contain two valid info\n";
	p += keyword_len;
	while (ft_isspace((unsigned char)*p))
		p++;
	if (*p == '\0' || contains_spaces(p))
		return (put_error(err_msg, "", 1));
	ft_memmove(*input_string, p, ft_strlen(p));
	(*input_string)[ft_strlen(p)] = '\0';
	return (0);
}

static int	read_file(t_all *data, int fd)
{
	char	*line;

	line = cub_get_next_line(fd, CLEAN_LINE);
	if (line == NULL && errno == 0)
		return (put_error("Error\nEmpty file\n", strerror(errno), EXIT_FAILURE));
	while (line)
	{
		if (store_settings(data, &line) == 1)
		{
			data->temp_data.flags = -1;
			free(line);
			line = cub_get_next_line(fd, STOP_READING);
			return (EXIT_FAILURE);
		}
		if (data->temp_data.flags == 63)
			break ;
		line = cub_get_next_line(fd, CLEAN_LINE);
	}
	if (errno)
		return (put_error("Error\n", strerror(errno), EXIT_FAILURE));
	if (data->temp_data.flags != 63)
		return (put_error("Error\nIncomplete settings\n", "", EXIT_FAILURE));
	return (parse_map(data, fd));
}

static void	init_textures_info(t_temp_data *temp)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		temp->textures_info[i].image = NULL;
		temp->textures_info[i].path = NULL;
		i++;
	}
	temp->mlx = NULL;
}

static void	init_data(t_all *data, char *path)
{
	char	*err_msg;

	err_msg = "Error\nMalloc failed\n";
	data->temp_data.flags = 0;
	data->temp_data.has_start = 0;
	data->temp_data.successful = 0;
	init_textures_info(&data->temp_data);
	data->temp_data.path_name = malloc((ft_strlen(path) + 1) * sizeof(char));
	data->map.tab = ft_calloc(LIST_INITIAL_SIZE, sizeof(char *));
	if (data->temp_data.path_name == NULL || data->map.tab == NULL)
	{
		del_data(data);
		exit(put_error(err_msg, "", EXIT_FAILURE));
	}
}

int	parse_data(t_all *data, char *path)
{
	int		fd;

	init_data(data, path);
	ft_strcpy(data->temp_data.path_name, path);
	fd = open(data->temp_data.path_name, O_RDONLY);
	data->temp_data.fd = fd;
	if (fd < 0)
	{
		del_data(data);
		return (put_error("Error\nCouldn't open the file.\n", "", EXIT_FAILURE));
	}
	read_file(data, fd);
	if (data->temp_data.successful)
		read_texture(data, &data->temp_data);
	if (data->temp_data.successful == 0)
		del_data(data);
	return (data->temp_data.successful);
}
