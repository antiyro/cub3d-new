/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:09:49 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 14:09:45 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_floor(char *line, t_ctrl *ctrl)
{
	int		i;
	char	**tab;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(line + i) < 7)
		return (FAILURE);
	if (line[i] == 'F')
	{
		i++;
		while (line[i] == ' ')
			i++;
		tab = ft_split(line + i, ',');
		if (!tab || rgbchecker(tab) == FAILURE)
			return (ft_freechartab(tab));
		ctrl->f_colors = tabchartotabint(tab);
		ft_freechartab(tab);
		if (!ctrl->f_colors)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	check_ceilling(char *line, t_ctrl *ctrl)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (line[i] == ' ')
		i++;
	if (line[i] == 'C')
	{
		i++;
		while (line[i] == ' ')
			i++;
		tab = ft_split(line + i, ',');
		if (!tab || rgbchecker(tab) == FAILURE)
			return (ft_freechartab(tab));
		ctrl->c_colors = tabchartotabint(tab);
		ft_freechartab(tab);
		if (!ctrl->c_colors)
			return (FAILURE);
		return (SUCCESS);
	}
	return (FAILURE);
}

unsigned long	rgbtohexa(int r, int g, int b)
{
	unsigned long	color;

	color = (r & 0xFF) << 16;
	color += (g & 0xFF) << 8;
	color += b & 0xFF;
	return (color);
}
