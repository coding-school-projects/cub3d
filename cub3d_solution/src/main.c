/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:26:37 by pchennia          #+#    #+#             */
/*   Updated: 2024/10/29 15:20:49 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct1(t_all *data)
{
	t_win		win;
	t_img		img;
	t_dir		dir;

	win.ptr = NULL;
	win.x = WIN_WIDTH;
	win.y = WIN_HEIGHT;
	img.ptr = NULL;
	img.adr = NULL;
	dir.x = 0;
	dir.y = 0;
	data->mlx = NULL;
	data->pos_x = 0;
	data->pos_y = 0;
	data->win = win;
	data->img = img;
	data->dir = dir;
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

int	render_game(t_all *data)
{
	init_ray(data);
	mlx_mouse_hide(data->mlx, data->win.ptr);
	mlx_hook(data->win.ptr, 2, 1L << 0, &key_hold, data);
	mlx_hook(data->win.ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->win.ptr, 17, 0L, &close_window, data);
	mlx_loop_hook(data->mlx, movement, data);
	mlx_loop(data->mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_all		data;

	if (argc != 2)
		return (put_error("Error\nExpects one parameter\n", "", EXIT_FAILURE));
	if (!valid_name(argv[1]))
		return (EXIT_FAILURE);
	init_struct1(&data);
	init_struct2(&data);
	if (!parse_data(&data, argv[1]) || !init_window(&data))
		return (1);
	render_game(&data);
	return (0);
}
