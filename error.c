/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 05:00:57 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/14 10:29:58 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free(void *content)
{
	free(content);
	content = NULL;
}

int	ft_freechartab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (FAILURE);
	while (tab && tab[i])
	{
		ft_free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
	return (FAILURE);
}

void	ft_freemlx(t_ctrl *ctrl)
{
	int	i;

	i = 0;
	if (ctrl->win.win_ptr)
		mlx_destroy_window(ctrl->win.mlx_ptr, ctrl->win.win_ptr);
	if (ctrl->win.img.ptr)
		mlx_destroy_image(ctrl->win.mlx_ptr, ctrl->win.img.ptr);
	while (i < 4)
	{
		if (ctrl->tex[i].img.ptr)
			mlx_destroy_image(ctrl->win.mlx_ptr, ctrl->tex[i].img.ptr);
		i++;
	}
	if (ctrl->win.mlx_ptr)
		mlx_destroy_display(ctrl->win.mlx_ptr);
	if (ctrl->win.mlx_ptr)
		ft_free(ctrl->win.mlx_ptr);
}

int	ft_freestruct(t_ctrl *ctrl, bool ctrlinit, int ret)
{
	if (ctrl->no_path)
		ft_free(ctrl->no_path);
	if (ctrl->so_path)
		ft_free(ctrl->so_path);
	if (ctrl->we_path)
		ft_free(ctrl->we_path);
	if (ctrl->ea_path)
		ft_free(ctrl->ea_path);
	if (ctrl->f_colors)
		ft_free(ctrl->f_colors);
	if (ctrl->c_colors)
		ft_free(ctrl->c_colors);
	if (ctrl->map)
		ft_freechartab(ctrl->map);
	if (ctrlinit)
		ft_freemlx(ctrl);
	return (ret);
}

int	ft_error(int err, t_ctrl *ctrl, bool ctrlinit)
{
	if (err == ARG)
		ft_putstr_fd("Error\nWrong number of argument\n", 2);
	else if (err == FILENAME)
		ft_putstr_fd("Error\nWrong file name/path\n", 2);
	else if (err == OPEN)
		ft_putstr_fd("Error\nopen error\n", 2);
	else if (err == MAPERROR)
		ft_putstr_fd("Error\nMap error\n", 2);
	else if (err == HEADERROR)
		ft_putstr_fd("Error\nHead error\n", 2);
	else
		ft_putstr_fd("Error\n", 2);
	if (ctrlinit)
		ft_freemlx(ctrl);
	return (FAILURE);
}
