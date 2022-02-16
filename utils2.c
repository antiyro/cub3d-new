/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:08:26 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 18:09:31 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	size_t	i;
	size_t	l;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	l = 0;
	res = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	if (s1)
	{
		while (s1[i])
		{
			res[i] = s1[i];
			i++;
		}
	}
	while (s2[l])
		res[i++] = s2[l++];
	res[i] = 0;
	free(s1);
	s1 = NULL;
	return (res);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	between0and255(int nb)
{
	if (nb >= 0 && nb <= 255)
		return (1);
	return (0);
}

int	rgbchecker(char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	if (i != 3)
		return (FAILURE);
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (!ft_isdigit(tab[i][j]))
				return (FAILURE);
			j++;
		}
		if (j > 3 || !between0and255(ft_atoi(tab[i])))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
