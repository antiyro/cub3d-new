/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:17:57 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 17:51:43 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_ischarset(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

int	ft_count(char *str, char charset)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i] && !ft_ischarset(str[i], charset))
		{
			c++;
			while (str[i] && !ft_ischarset(str[i], charset))
				i++;
		}
		else
			i++;
	}
	return (c);
}

char	*ft_fill(char *str, char charset, int *ptr_i)
{
	char	*tab;
	int		j;

	j = 0;
	while (str[*ptr_i] && ft_ischarset(str[*ptr_i], charset))
		(*ptr_i)++;
	while (str[*ptr_i + j] && !ft_ischarset(str[*ptr_i + j], charset))
		j++;
	tab = malloc(sizeof(char) * (j + 1));
	if (!tab)
		return (NULL);
	j = 0;
	while (str[*ptr_i] && !ft_ischarset(str[*ptr_i], charset))
	{
		tab[j] = str[*ptr_i];
		j++;
		(*ptr_i)++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	char	*str;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	str = (char *)s;
	l = ft_count(str, c);
	tab = malloc(sizeof(char *) * (l + 1));
	if (!tab)
		return (NULL);
	while (j < l)
	{
		tab[j] = ft_fill(str, c, &i);
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
