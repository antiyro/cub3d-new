/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 17:20:12 by nbouhada          #+#    #+#             */
/*   Updated: 2021/11/23 11:43:22 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			mult;
	long long	nb;

	i = 0;
	mult = 1;
	nb = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			mult *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb * mult > 2147483647)
			return (-1);
		else if (nb * mult < -2147483648)
			return (0);
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	return ((int)nb * mult);
}
