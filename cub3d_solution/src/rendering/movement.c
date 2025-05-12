/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:15:53 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 13:43:41 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_screen(t_all *data)
{
	while (data->ray.angle_index < data->win.x)
	{
		calculate_ray_vector(data);
		identify_ray_direction(data);
		find_vertical_wall_hit(data);
		find_horizontal_wall_hit(data);
		display_vertical_wall_section(data, height_of_wall(data));
		data->ray.angle_index++;
	}
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

int	movement(t_all *data)
{
	static int	once;

	if (data->key_control & GO_FORWARD)
		move_forward_or_back(data, 1);
	else if (data->key_control & GO_RIGHT)
		move_left_or_right(data, 1);
	else if (data->key_control & GO_BACKWARD)
		move_forward_or_back(data, -1);
	else if (data->key_control & GO_LEFT)
		move_left_or_right(data, -1);
	else if (data->key_control & LOOK_LEFT)
		rotate_left_right(data, -1);
	else if (data->key_control & LOOK_RIGHT)
		rotate_left_right(data, 1);
	else if (once == 0)
		once = 1;
	else
		return (0);
	data->ray.angle_index = 0;
	display_screen(data);
	mlx_put_image_to_window(data->mlx, data->win.ptr, data->img.ptr, 0, 0);
	data->key_control = 0;
	return (0);
}
