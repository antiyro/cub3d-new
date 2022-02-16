/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 04:55:49 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/14 10:34:15 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_read(int fd)
{
	char	buf[1];
	char	*str;
	int		ret;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	ret = read(fd, buf, 1);
	while (ret)
	{
		if (ret == -1)
			return (NULL);
		str = ft_strjoin(str, buf);
		if (!str)
			return (NULL);
		ret = read(fd, buf, 1);
	}
	return (str);
}

void	verifemptyline2(char *str, int *count, int *i)
{
	while (str && str[*i])
	{
		if (str[*i] && str[*i + 1] && str[*i] == 'N' && str[*i + 1] == 'O')
			(*count)++;
		else if (str[*i] && str[*i + 1] && str[*i] == 'S' && str[*i + 1] == 'O')
			(*count)++;
		else if (str[*i] && str[*i + 1] && str[*i] == 'W' && str[*i + 1] == 'E')
			(*count)++;
		else if (str[*i] && str[*i + 1] && str[*i] == 'E' && str[*i + 1] == 'A')
			(*count)++;
		else if (str[*i] && str[*i + 1] && str[*i] == 'C' && str[*i + 1] == ' ')
			(*count)++;
		else if (str[*i] && str[*i + 1] && str[*i] == 'F' && str[*i + 1] == ' ')
			(*count)++;
		if (*count == 6)
		{
			while (str && str[*i] && str[*i] != '\n')
				(*i)++;
			while (str && str[*i] && (str[*i] == '\n' || str[*i] == ' '))
				(*i)++;
			break ;
		}
		(*i)++;
	}
}

int	isfinish(char *str, int i)
{
	while (str && str[i])
	{
		if (str && str[i] && str[i] != '\n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	verifemptyline(char *str)
{
	int	i;
	int	count;

	if (!str)
		return (MAPERROR);
	i = 0;
	count = 0;
	verifemptyline2(str, &count, &i);
	if (count != 6)
	{
		ft_free(str);
		return (MAPERROR);
	}
	while (str && str[i])
	{
		if (str && str[i] && str[i + 1] && str[i] == '\n' && str[i + 1] == '\n')
		{
			if (isfinish(str, i) == SUCCESS)
				return (SUCCESS);
			ft_free(str);
			return (MAPERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	parsing(int fd, t_ctrl *ctrl)
{
	char	*str;
	char	**tab;

	str = ft_read(fd);
	if (verifemptyline(str) == MAPERROR)
		return (MAPERROR);
	tab = ft_split(str, '\n');
	if (!tab)
		return (FAILURE);
	free(str);
	if (check_head(tab, ctrl))
	{
		ft_freechartab(tab);
		return (ft_freestruct(ctrl, false, HEADERROR));
	}
	ctrl->map = realloc_tab(tab);
	if (!ctrl->map)
	{
		ft_freechartab(tab);
		return (ft_freestruct(ctrl, false, FAILURE));
	}
	ft_freechartab(tab);
	if (check_map(ctrl) == MAPERROR)
		return (ft_freestruct(ctrl, false, MAPERROR));
	return (SUCCESS);
}
