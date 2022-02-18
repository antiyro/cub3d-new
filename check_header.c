/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 08:42:45 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 15:55:26 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_north(char *line, t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(line + i) < 6)
		return (FAILURE);
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		i += 2;
		if (line[i] == '.')
			return (FAILURE);
		while (line[i] == ' ')
			i++;
		if (line[i] == '.' && line[i + 1] == '/' && line[i + 2])
		{
			ctrl->no_path = ft_strdup(line + (i + 2));
			if (!ctrl->no_path)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	check_south(char *line, t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(line + i) < 6)
		return (FAILURE);
	if (line[i] == 'S' && line[i + 1] == 'O')
	{
		i += 2;
		if (line[i] == '.')
			return (FAILURE);
		while (line[i] == ' ')
			i++;
		if (line[i] == '.' && line[i + 1] == '/' && line[i + 2])
		{
			ctrl->so_path = ft_strdup(line + (i + 2));
			if (!ctrl->so_path)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	check_west(char *line, t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(line + i) < 6)
		return (FAILURE);
	if (line[i] == 'W' && line[i + 1] == 'E')
	{
		i += 2;
		if (line[i] == '.')
			return (FAILURE);
		while (line[i] == ' ')
			i++;
		if (line[i] == '.' && line[i + 1] == '/' && line[i + 2])
		{
			ctrl->we_path = ft_strdup(line + (i + 2));
			if (!ctrl->we_path)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	check_east(char *line, t_ctrl *ctrl)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strlen(line + i) < 6)
		return (FAILURE);
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		i += 2;
		if (line[i] == '.')
			return (FAILURE);
		while (line[i] == ' ')
			i++;
		if (line[i] == '.' && line[i + 1] == '/' && line[i + 2])
		{
			ctrl->ea_path = ft_strdup(line + (i + 2));
			if (!ctrl->ea_path)
				return (FAILURE);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int	*tabchartotabint(char **tab)
{
	int	i;
	int	*tabint;

	i = 0;
	tabint = malloc(sizeof(int) * 3);
	if (!tabint)
		return (NULL);
	while (tab[i])
	{
		tabint[i] = ft_atoi(tab[i]);
		i++;
	}
	return (tabint);
}
