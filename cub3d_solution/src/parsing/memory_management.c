/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 05:30:20 by olmohame          #+#    #+#             */
/*   Updated: 2024/10/17 02:35:08 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map(char **list)
{
	int	i;

	if (!list)
		return ;
	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
	list = NULL;
}

static void	del_textures_info(t_temp_data *temp)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (temp->mlx && temp->textures_info[i].image)
			mlx_destroy_image(temp->mlx, temp->textures_info[i].image);
		if (temp->textures_info[i].path)
		{
			free(temp->textures_info[i].path);
			temp->textures_info[i].path = NULL;
		}
		i++;
	}
	if (temp->mlx == NULL)
		return ;
	mlx_destroy_display(temp->mlx);
	if (temp->mlx)
		free(temp->mlx);
	temp->mlx = NULL;
}

void	del_data(t_all *data)
{
	del_textures_info(&data->temp_data);
	free_map(data->map.tab);
	data->map.tab = NULL;
	free(data->temp_data.path_name);
	data->temp_data.path_name = NULL;
}
