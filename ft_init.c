/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:56:16 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 16:46:48 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialisation de la mlx/fenetre
 * 
 * @param ctrl 
 * @return int 
 */
int	ft_init_win(t_ctrl *ctrl)
{
	ctrl->win.win_coord.x = ft_strlen(ctrl->map[0]);
	ctrl->win.win_coord.y = ft_tablen(ctrl->map);
	ctrl->win.mlx_ptr = mlx_init();
	if (!ctrl->win.mlx_ptr)
		return (1);
	mlx_get_screen_size(ctrl->win.mlx_ptr, &ctrl->win.win_coord.x,
		&ctrl->win.win_coord.y);
	ctrl->win.win_ptr = mlx_new_window(ctrl->win.mlx_ptr, ctrl->win.win_coord.x,
			ctrl->win.win_coord.y, "Cub3D");
	if (!ctrl->win.win_ptr)
		return (1);
	ctrl->win.img.ptr = mlx_new_image(ctrl->win.mlx_ptr, ctrl->win.win_coord.x,
			ctrl->win.win_coord.y);
	if (!ctrl->win.img.ptr)
		return (1);
	ctrl->win.img.addr = (int *)mlx_get_data_addr(ctrl->win.img.ptr,
			&ctrl->win.img.bpp, &ctrl->win.img.size_line,
			&ctrl->win.img.endian);
	if (!ctrl->win.img.addr)
		return (1);
	return (0);
}

/**
 * @brief Reinitialisation du rayon : x = 0 + movespeed/rotspeed
 * 
 * @param ctrl 
 * @return int 
 */
int	ft_init_ray(t_ctrl *ctrl)
{
	ctrl->ray.moveSpeed = 0.2;
	ctrl->ray.rotSpeed = 0.1;
	ctrl->ray.x = 0;
	return (0);
}

/**
 * @brief Recuperation de l'addresse des textures pour 
 * ensuite imprimer les pixels necessaire
 * 
 * @param tex 
 */
void	ft_get_texture_addr(t_tex_img *tex)
{
	tex[0].img.addr = (int *)mlx_get_data_addr(tex[0].img.ptr, &tex[0].img.bpp,
			&tex[0].img.size_line, &tex->img.endian);
	tex[1].img.addr = (int *)mlx_get_data_addr(tex[1].img.ptr, &tex[1].img.bpp,
			&tex[1].img.size_line, &tex->img.endian);
	tex[2].img.addr = (int *)mlx_get_data_addr(tex[2].img.ptr, &tex[2].img.bpp,
			&tex[2].img.size_line, &tex->img.endian);
	tex[3].img.addr = (int *)mlx_get_data_addr(tex[3].img.ptr, &tex[3].img.bpp,
			&tex[3].img.size_line, &tex->img.endian);
}

/**
 * @brief Conversion des .xpm vers pointeurs void *
 * 
 * @param ctrl 
 * @param tex Tableau de structure contenant les infos de chaque texure
 * @return int 
 */
int	ft_init_textures(t_ctrl *ctrl, t_tex_img *tex)
{
	tex[0].img.ptr = mlx_xpm_file_to_image(ctrl->win.mlx_ptr,
			ctrl->no_path, &tex[0].width, &tex[0].height);
	tex[1].img.ptr = mlx_xpm_file_to_image(ctrl->win.mlx_ptr,
			ctrl->so_path, &tex[1].width, &tex[1].height);
	tex[2].img.ptr = mlx_xpm_file_to_image(ctrl->win.mlx_ptr,
			ctrl->we_path, &tex[2].width, &tex[2].height);
	tex[3].img.ptr = mlx_xpm_file_to_image(ctrl->win.mlx_ptr,
			ctrl->ea_path, &tex[3].width, &tex[3].height);
	ft_get_texture_addr(tex);
	return (0);
}

/**
 * @brief Initialisation generale
 * 
 * @param ctrl 
 * @return int 
 */
int	ft_init(t_ctrl *ctrl)
{
	ft_init_win(ctrl);
	ft_init_textures(ctrl, ctrl->tex);
	return (0);
}
