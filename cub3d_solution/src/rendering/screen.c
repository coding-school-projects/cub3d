/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchennia <pchennia@student.42.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:23:46 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 11:04:38 by pchennia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_wall_tex_color(t_all *s, double i)
{
	int	index;

	if (floor(s->hit.y) == s->hit.y)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.x - floor(s->hit.x));
		if (s->ray.h == 1)
			return (s->tex.s[index]);
		else if (s->ray.h == 0)
			return (s->tex.n[index]);
	}
	else if (floor(s->hit.x) == s->hit.x)
	{
		index = 64 * floor(64 * i) + 64 * (s->hit.y - floor(s->hit.y));
		if (s->ray.v == 1)
			return (s->tex.e[index]);
		else if (s->ray.v == 0)
			return (s->tex.w[index]);
	}
	return (BLACK);
}

// ws_height = wallslice_height
// pixel_col = pixel_color
void	display_vertical_wall_section(t_all *s, int ws_height)
{
	unsigned int	pixel_col;
	int				col_startpoint;
	int				curr_pixel;

	col_startpoint = s->win.x * (s->win.y - ws_height) / 2;
	if (ws_height > s->win.y)
		curr_pixel = (ws_height - s->win.y) / 2;
	else
		curr_pixel = 0;
	pixel_col = s->tex.c;
	while (s->ray.angle_index < s->win.x * s->win.y)
	{
		if (s->ray.angle_index >= col_startpoint && curr_pixel < ws_height)
		{
			pixel_col = get_wall_tex_color(s, (double)curr_pixel / ws_height);
			curr_pixel++;
		}
		else if (curr_pixel == ws_height)
			pixel_col = s->tex.f;
		s->img.adr[s->ray.angle_index] = mlx_get_color_value(s->mlx, pixel_col);
		s->ray.angle_index += s->win.x;
	}
	s->ray.angle_index -= s->win.x * s->win.y;
}

int	height_of_wall(t_all *s)
{
	double	distance_to_wall;
	double	fisheye;
	int		wallslice_height;

	fisheye = fabs((double)s->ray.angle_index / (s->win.x / 2) - 1);
	fisheye *= 28 * M_PI / 180;
	distance_to_wall = (double)s->hit.d * cos(fisheye);
	wallslice_height = round(s->win.y / distance_to_wall);
	return (wallslice_height);
}
