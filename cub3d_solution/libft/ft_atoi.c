/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmohame <olmohame@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:16:04 by pchennia          #+#    #+#             */
/*   Updated: 2024/11/07 12:54:29 by olmohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "limits.h"

int	ft_isspace(char chr)
{
	if ((chr >= 9 && chr <= 13) || chr == ' ')
		return (1);
	return (0);
}

int	ft_only_spaces(const char *str)
{
	while (ft_isspace(*str))
		str++;
	return (*str == '\0');
}

int	ft_atoi(const char *nptr)
{
	unsigned long	ret_val;
	int				index;
	int				polarity;

	polarity = 1;
	index = 0;
	if (*nptr == '\0')
		return (0);
	while (ft_isspace(nptr[index]))
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			polarity *= -1;
		index++;
	}
	ret_val = 0;
	while (nptr[index] >= '0' && nptr[index] <= '9')
		ret_val = (ret_val * 10) + (nptr[index++] - '0');
	if (ret_val > LONG_MAX && polarity == -1)
		return (0);
	if (ret_val > LONG_MAX && polarity == 1)
		return (-1);
	return (ret_val * polarity);
}
