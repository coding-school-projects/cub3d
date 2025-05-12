/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:57:27 by pchennia          #+#    #+#             */
/*   Updated: 2024/10/29 16:20:46 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_struct1(t_all *data)
{
	t_win		win;
	t_img		img;
	t_dir		dir;
	t_minimap	minimap;

	win.ptr = NULL;
	win.x = WIN_WIDTH;
	win.y = WIN_HEIGHT;
	img.ptr = NULL;
	img.adr = NULL;
	dir.x = 0;
	dir.y = 0;
	minimap.img = img;
	minimap.cell_size = 10;
	data->mlx = NULL;
	data->pos_x = 0;
	data->pos_y = 0;
	data->win = win;
	data->img = img;
	data->dir = dir;
	data->minimap = minimap;
}

void	init_struct2(t_all *data)
{
	t_map	map;
	t_tex	tex;
	t_stk	*stk;

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	stk = NULL;
	map.x = 0;
	map.y = 0;
	tex.c = NONE;
	tex.f = NONE;
	data->map = map;
	data->tex = tex;
	data->stk = stk;
	data->key_control = 0;
}

int	init_window(t_all *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error: Failed to initialize mlx.\n");
		del_data(data);
		return (0);
	}
	data->win.ptr = mlx_new_window(data->mlx, data->win.x, data->win.y,
			"cub3D");
	if (!data->win.ptr)
	{
		printf("Error: Failed to create window.\n");
		del_data(data);
		return (0);
	}
	return (1);
}

void	init_minimap(t_all *data)
{
	int	bpp;
	int	sl;
	int	end;

	data->minimap.width = data->map.x * data->minimap.cell_size;
	data->minimap.height = data->map.y * data->minimap.cell_size;
	data->minimap.img.ptr = mlx_new_image(data->mlx, data->minimap.width,
			data->minimap.height);
	data->minimap.img.adr = (unsigned int *)mlx_get_data_addr(
			data->minimap.img.ptr, &bpp, &sl, &end);
}
