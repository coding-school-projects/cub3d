/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 04:50:04 by olmohame          #+#    #+#             */
/*   Updated: 2024/11/03 13:07:53 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_direction(int direction[8][2])
{
	direction[0][0] = -1;
	direction[0][1] = -1;
	direction[1][0] = -1;
	direction[1][1] = 0;
	direction[2][0] = -1;
	direction[2][1] = 1;
	direction[3][0] = 0;
	direction[3][1] = -1;
	direction[4][0] = 0;
	direction[4][1] = 1;
	direction[5][0] = 1;
	direction[5][1] = -1;
	direction[6][0] = 1;
	direction[6][1] = 0;
	direction[7][0] = 1;
	direction[7][1] = 1;
}

static int	is_valid_box(t_all *data,
						ssize_t x, ssize_t y, int direction[8][2])
{
	int		d;
	ssize_t	adj_x;
	ssize_t	adj_y;

	if (x == 0 || y == 0 || x == data->map.x - 1 || y == data->map.y - 1)
	{
		return (put_error("Error\nThe map is not surrounded by walls\n", "", 0));
	}
	d = 0;
	while (d < 8)
	{
		adj_x = x + direction[d][0];
		adj_y = y + direction[d][1];
		if (adj_x >= 0 && adj_x < data->map.x
			&& adj_y >= 0 && adj_y < data->map.y)
		{
			if (ft_isspace(data->map.tab[adj_y][adj_x]))
			{
				put_error("Error\nThe map is not surrounded by walls\n", "", 1);
				return (0);
			}
		}
		d++;
	}
	return (1);
}

int	map_contained(t_all *data)
{
	ssize_t	i;
	ssize_t	j;
	int		direction[8][2];

	init_direction(direction);
	j = 0;
	while (j < data->map.y)
	{
		i = 0;
		while (i < data->map.x)
		{
			if (data->map.tab[j][i] == '0'
					|| ft_strchr(PLAYER_ORIENTATION_CHARS, data->map.tab[j][i]))
			{
				if (!is_valid_box(data, i, j, direction))
					return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}
