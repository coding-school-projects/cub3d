/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 23:26:37 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 13:44:07 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	render_game(t_all *data)
{
	init_ray(data);
	init_minimap(data);
	mlx_mouse_hide(data->mlx, data->win.ptr);
	mlx_hook(data->win.ptr, 2, 1L << 0, &key_hold, data);
	mlx_hook(data->win.ptr, 3, 1L << 1, key_release, data);
	mlx_hook(data->win.ptr, 17, 0L, &close_window, data);
	mlx_loop_hook(data->mlx, movement, data);
	mlx_loop(data->mlx);
	return (1);
}

int	close_window(t_all *data)
{
	mlx_mouse_show(data->mlx, data->win.ptr);
	free(data->stk);
	del_data(data);
	if (data->img.ptr)
	{
		mlx_destroy_image(data->mlx, data->img.ptr);
		data->img.ptr = NULL;
	}
	if (data->minimap.img.ptr)
	{
		mlx_destroy_image(data->mlx, data->minimap.img.ptr);
		data->minimap.img.ptr = NULL;
	}
	if (data->win.ptr)
	{
		mlx_destroy_window(data->mlx, data->win.ptr);
		data->win.ptr = NULL;
	}
	mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
	data->mlx = NULL;
	exit (0);
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
