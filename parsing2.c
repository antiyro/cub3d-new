/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 04:59:53 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/14 10:33:30 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dir_init(char c, t_ctrl *ctrl)
{
	if (c == 'N')
	{
		ctrl->ray.dir.x = -1;
		ctrl->ray.plane.y = 0.66;
	}
	else if (c == 'S')
	{
		ctrl->ray.dir.x = 1;
		ctrl->ray.plane.y = -0.66;
	}
	else if (c == 'E')
	{
		ctrl->ray.dir.y = 1;
		ctrl->ray.plane.x = 0.66;
	}
	else if (c == 'W')
	{
		ctrl->ray.dir.y = -1;
		ctrl->ray.plane.x = -0.66;
	}
}

int	check_map2(t_ctrl *ctrl, int *i, int *j, int *countpos)
{
	while (ctrl->map[*i][*j])
	{
		if (check_close(*i, *j, ctrl->map))
			return (MAPERROR);
		if (!check_space_wall(ctrl->map[*i][*j]))
		{
			(*j)++;
			continue ;
		}
		if (!check_character(ctrl->map[*i][*j]))
		{
			ctrl->ray.pos.x = *i + 0.5;
			ctrl->ray.pos.y = *j + 0.5;
			dir_init(ctrl->map[*i][*j], ctrl);
			ctrl->map[*i][*j] = '0';
			(*countpos)++;
			(*j)++;
			continue ;
		}
		return (MAPERROR);
	}
	return (SUCCESS);
}

int	check_map(t_ctrl *ctrl)
{
	int	i;
	int	j;
	int	countpos;

	i = 0;
	countpos = 0;
	while (ctrl->map && ctrl->map[i])
	{
		j = 0;
		if (check_map2(ctrl, &i, &j, &countpos) == MAPERROR)
			return (MAPERROR);
		i++;
	}
	if (countpos == 1)
		return (SUCCESS);
	return (MAPERROR);
}

int	ft_fill_map(char **tab, char **map, int max_length, int l)
{
	int	i;
	int	j;

	i = 0;
	(void)max_length;
	while (i < l - 1)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * ft_strlen(tab[i + 6]) + 1);
		if (!map[i])
			return (FAILURE);
		while (j < ft_strlen(tab[i + 6]))
		{
			if (tab[i + 6] && tab[i + 6][j] && tab[i + 6][j] == ' ')
				map[i][j] = '1';
			else
				map[i][j] = tab[i + 6][j];
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (SUCCESS);
}

char	**realloc_tab(char **tab)
{
	char	**map;
	int		i;
	int		max_length_line;

	i = 6;
	max_length_line = 0;
	while (tab[i])
	{
		if (ft_strlen(tab[i]) > max_length_line)
			max_length_line = ft_strlen(tab[i]);
		i++;
	}
	map = malloc(sizeof(char *) * i - 6 + 1);
	if (!map)
		return (NULL);
	if (ft_fill_map(tab, map, max_length_line, i - 6 + 1) == FAILURE)
		return (NULL);
	return (map);
}
