/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 04:56:56 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 18:07:19 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_space_wall(char c)
{
	if (c == '0' || c == '1')
		return (SUCCESS);
	return (FAILURE);
}

int	check_character(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (SUCCESS);
	return (FAILURE);
}

int	check_close(int i, int j, char **map)
{
	if ((i == 0 && map[i][j] != '1') || (j == 0 && map[i][j] != '1')
			|| (j == ft_strlen(map[i]) - 1 && map[i][j] != '1')
			|| (i == ft_tablen(map) - 1 && map[i][j] != '1')
			|| (map[i][j] != '1' && i > 0 && i < ft_tablen(map)
				&& (j > ft_strlen(map[i - 1]) - 1
					|| j > ft_strlen(map[i + 1]) - 1)))
		return (FAILURE);
	return (SUCCESS);
}

int	check_head(char **tab, t_ctrl *ctrl)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < 6)
	{
		if ((!ctrl->no_path && !check_north(tab[i], ctrl))
			|| (!ctrl->so_path && !check_south(tab[i], ctrl))
			|| (!ctrl->we_path && !check_west(tab[i], ctrl))
			|| (!ctrl->ea_path && !check_east(tab[i], ctrl))
			|| (!ctrl->f_colors && !check_floor(tab[i], ctrl))
			|| (!ctrl->c_colors && !check_ceilling(tab[i], ctrl)))
			count++;
		else
			return (HEADERROR);
		i++;
	}
	if (count == 6)
		return (SUCCESS);
	return (HEADERROR);
}

int	check_file(char *path)
{
	int	i;

	i = ft_strlen(path);
	if (i < 5)
		return (FAILURE);
	i--;
	if (!(path[i] == 'b' && path[i - 1] == 'u'
			&& path[i - 2] == 'c' && path[i - 3] == '.'
			&& path[i - 4]))
		return (FAILURE);
	return (SUCCESS);
}
