/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 22:56:23 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 13:46:15 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left_right(t_all *data, double c)
{
	double	dist;

	data->dir.x = data->dir.x * cos(c * TURN) - data->dir.y * sin(c * TURN);
	data->dir.y = data->dir.y * cos(c * TURN) + data->dir.x * sin(c * TURN);
	dist = hypot(data->dir.x, data->dir.y);
	data->dir.x /= dist;
	data->dir.y /= dist;
}

void	move_forward_or_back(t_all *data, double c)
{
	double	temp1;
	double	temp2;

	data->pos_x += c * (data->dir.x * SPEED / 100);
	temp1 = data->map.x - 1.10;
	if (data->pos_x >= temp1)
		data->pos_x -= c * (data->dir.x * SPEED / 100);
	data->pos_y += c * (data->dir.y * SPEED / 100);
	temp2 = data->map.y - 1.10;
	if (data->pos_y >= temp2 || data->pos_y <= 1.10)
		data->pos_y -= c * (data->dir.y * SPEED / 100);
}

void	move_left_or_right(t_all *data, double c)
{
	double	temp1;
	double	temp2;

	data->pos_x -= c * (data->dir.y * SPEED / 100);
	temp1 = data->map.x - 1.10;
	if (data->pos_x >= temp1 || data->pos_x <= 1.10)
		data->pos_x += c * (data->dir.y * SPEED / 100);
	data->pos_y += c * (data->dir.x * SPEED / 100);
	temp2 = data->map.y - 1.10;
	if (data->pos_y >= temp2)
		data->pos_y -= c * (data->dir.x * SPEED / 100);
}

int	key_hold(int key, void *arg)
{
	if (key == ESC)
		close_window(arg);
	else if (key == W)
		((t_all *)arg)->key_control |= GO_FORWARD;
	else if (key == A)
		((t_all *)arg)->key_control |= GO_LEFT;
	else if (key == S)
		((t_all *)arg)->key_control |= GO_BACKWARD;
	else if (key == D)
		((t_all *)arg)->key_control |= GO_RIGHT;
	else if (key == LEFT)
		((t_all *)arg)->key_control |= LOOK_LEFT;
	else if (key == RIGHT)
		((t_all *)arg)->key_control |= LOOK_RIGHT;
	return (1);
}

int	key_release(int key, void *arg)
{
	if (key == W)
		((t_all *)arg)->key_control &= ~GO_FORWARD;
	else if (key == A)
		((t_all *)arg)->key_control &= ~GO_LEFT;
	else if (key == S)
		((t_all *)arg)->key_control &= ~GO_BACKWARD;
	else if (key == D)
		((t_all *)arg)->key_control &= ~GO_RIGHT;
	else if (key == LEFT)
		((t_all *)arg)->key_control &= ~LOOK_LEFT;
	else if (key == RIGHT)
		((t_all *)arg)->key_control &= ~LOOK_RIGHT;
	return (1);
}
