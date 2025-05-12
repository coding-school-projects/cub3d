/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:58:25 by olmohame          #+#    #+#             */
/*   Updated: 2024/11/03 13:02:29 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_number(char **str)
{
	size_t	digit_count;
	int		num;

	num = 0;
	digit_count = 0;
	while (ft_isdigit((unsigned char)**str))
	{
		digit_count++;
		if (digit_count > 3 && num > 100)
			num = 404;
		else
			num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

static int	check_rgb_range(t_color color)
{
	int		out_of_range;
	char	*err_msg;

	err_msg = "Error\nR,G,B colors should be in the range [0,255]\n";
	out_of_range = (color.r > 255 || color.g > 255 || color.b > 255);
	if (out_of_range)
		put_error(err_msg, "", EXIT_FAILURE);
	return (out_of_range);
}

static int	combine_rgb(t_color color)
{
	int	temp;

	temp = ((color.r & 0xff) << 16) + \
	((color.g & 0xff) << 8) + (color.b & 0xff);
	return (temp);
}

static int	read_color(t_all *data,
				char **input_string, int color_index)
{
	char	*err_msg;
	char	*temp;
	t_color	color;

	temp = *input_string;
	err_msg = "Error\nThe color is expected in the form <R,G,B>\n";
	if (ft_count_words(temp, ',') != 3)
		return (put_error(err_msg, "", EXIT_FAILURE));
	err_msg = "Error\nUnexpected character found while parsing the color\n";
	color.r = parse_number(&temp);
	if (temp[0] == ',' && ft_isdigit(temp[1]))
		temp++;
	color.g = parse_number(&temp);
	if (temp[0] == ',' && ft_isdigit(temp[1]))
		temp++;
	color.b = parse_number(&temp);
	if (color_index)
		data->tex.c = combine_rgb(color);
	else
		data->tex.f = combine_rgb(color);
	if (temp[0] != '\0')
		return (put_error(err_msg, "", EXIT_FAILURE));
	return (check_rgb_range(color));
}

int	store_color(t_all *data, char **line,
					int color_index, const char *keyword)
{
	int		flag;
	char	*err_msg;

	flag = F_FLAG;
	if (color_index)
		flag = C_FLAG;
	err_msg = "Error\nRedundant settings for color\n";
	if (data->temp_data.flags & flag)
		return (put_error(err_msg, "", EXIT_FAILURE));
	if (validate_and_clean(line, keyword))
		return (EXIT_FAILURE);
	if (read_color(data, line, color_index))
		return (EXIT_FAILURE);
	data->temp_data.flags |= flag;
	free(*line);
	*line = 0;
	return (EXIT_SUCCESS);
}
