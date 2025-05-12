/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 02:24:40 by olmohame          #+#    #+#             */
/*   Updated: 2024/10/29 15:46:19 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_textures(int *flags)
{
	flags[0] = NO_FLAG;
	flags[1] = SO_FLAG;
	flags[2] = EA_FLAG;
	flags[3] = WE_FLAG;
}

int	store_texture(t_temp_data *data, char **line,
					int texture_index, const char *keyword)
{
	int		texture_flags[4];
	char	*err_msg;
	int		flag;

	err_msg = "Error\nRedundant settings for texture\n";
	init_textures(texture_flags);
	flag = texture_flags[texture_index];
	if (data->flags & flag)
		return (put_error(err_msg, "", EXIT_FAILURE));
	if (validate_and_clean(line, keyword))
		return (EXIT_FAILURE);
	data->textures_info[texture_index].path = *line;
	data->flags |= flag;
	return (EXIT_SUCCESS);
}

static unsigned int	*load_xpm_image(t_temp_data *temp, t_texture *texture)
{
	int		bpp;
	int		size_line;
	int		endian;
	int		w;
	int		h;

	texture->image = mlx_xpm_file_to_image(temp->mlx, texture->path, &w, &h);
	if (!texture->image)
	{
		put_error("Error\nCould not load XPM file.\n", "", 0);
		return (0);
	}
	return ((unsigned int *)mlx_get_data_addr(\
			texture->image, &bpp, &size_line, &endian));
}

int	read_texture(t_all *data, t_temp_data *temp)
{
	char	*err_msg;

	temp->successful = 0;
	err_msg = "Error\nCould not initialize MiniLibX.\n";
	temp->mlx = mlx_init();
	if (!temp->mlx)
		return (put_error(err_msg, "", EXIT_FAILURE));
	data->tex.n = load_xpm_image(temp, &temp->textures_info[0]);
	data->tex.s = load_xpm_image(temp, &temp->textures_info[1]);
	data->tex.e = load_xpm_image(temp, &temp->textures_info[2]);
	data->tex.w = load_xpm_image(temp, &temp->textures_info[3]);
	if (data->tex.n && data->tex.s && data->tex.e && data->tex.w)
		temp->successful = 1;
	return (0);
}
