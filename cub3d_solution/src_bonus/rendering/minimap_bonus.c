/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:30:44 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 10:58:04 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_line(t_all *data, t_stk startpoint, t_stk endpoint, long color)
{
	double	delta_x;
	double	delta_y;
	double	step;
	int		pixel_index;

	delta_x = endpoint.x - startpoint.x;
	delta_y = endpoint.y - startpoint.y;
	step = fabs(delta_y);
	if (fabs(delta_x) > fabs(delta_y))
		step = fabs(delta_x);
	delta_x /= step;
	delta_y /= step;
	while (fabs(endpoint.x - startpoint.x) > fabs(delta_x)
		|| fabs(endpoint.y - startpoint.y) > fabs(delta_y))
	{
		pixel_index = floor(startpoint.y) * floor(data->minimap.width) \
												+ floor(startpoint.x);
		data->minimap.img.adr[pixel_index] = color;
		startpoint.x += delta_x;
		startpoint.y += delta_y;
	}
}

void	draw_lines_in_minimap(t_all *data)
{
	t_stk	line_startpoint;
	t_stk	line_endpoint;
	int		i;

	i = -1;
	line_startpoint.y = 0;
	line_endpoint.y = data->minimap.height;
	while (++i < data->map.x)
	{
		line_startpoint.x = i * data->minimap.cell_size;
		line_endpoint.x = i * data->minimap.cell_size;
		draw_line(data, line_startpoint, line_endpoint, GRAY);
	}
	i = -1;
	line_startpoint.x = 0;
	line_endpoint.x = data->minimap.width;
	while (++i < data->map.y)
	{
		line_startpoint.y = i * data->minimap.cell_size;
		line_endpoint.y = i * data->minimap.cell_size;
		draw_line(data, line_startpoint, line_endpoint, GRAY);
	}
}

void	draw_rectangle(t_all *data, int x, int y, long color)
{
	int	i;
	int	j;

	x *= data->minimap.cell_size;
	y *= data->minimap.cell_size;
	i = 0;
	while (i < data->minimap.cell_size)
	{
		j = 0;
		while (j < data->minimap.cell_size)
		{
			data->minimap.img.adr[(y + i) * data->map.x
				* data->minimap.cell_size + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangles_in_minimap(t_all *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->map.y)
	{
		j = 0;
		while (data->map.tab[i][j])
		{
			if (data->map.tab[i][j] == '1')
				draw_rectangle(data, j, i, WHITE);
			else
				draw_rectangle(data, j, i, BLACK);
			j++;
		}
		i++;
	}
}

void	draw_player_in_minimap(t_all *data)
{
	int		i;
	t_stk	ray_startpoint;
	t_stk	ray_endpoint;

	i = 0;
	ray_startpoint.x = (ceil(data->pos_x) * data->minimap.cell_size)
		- (data->minimap.cell_size / 2);
	ray_startpoint.y = (ceil(data->pos_y) * data->minimap.cell_size)
		- (data->minimap.cell_size / 2);
	while (i < data->win.x)
	{
		ray_endpoint.x = ceil(data->stk[i].x * data->minimap.cell_size);
		ray_endpoint.y = ceil(data->stk[i].y * data->minimap.cell_size);
		draw_line(data, ray_startpoint, ray_endpoint, GREEN);
		i++;
	}
	draw_rectangle(data, (int)data->pos_x, (int)data->pos_y, RED);
}
