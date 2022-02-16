/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 23:54:54 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 17:44:23 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Gestion des actions : avancer et reculer
 * 
 * @param ctrl 
 */
void	move_forward_backward(t_ctrl *ctrl)
{
	if (ctrl->move.x == 1)
	{
		if (ctrl->map[(int)(ctrl->ray.pos.x + ctrl->ray.dir.x
				* ctrl->ray.moveSpeed)][(int)ctrl->ray.pos.y] == '0')
			ctrl->ray.pos.x += ctrl->ray.dir.x * ctrl->ray.moveSpeed;
		if (ctrl->map[(int)ctrl->ray.pos.x][(int)(ctrl->ray.pos.y
			+ ctrl->ray.dir.y * ctrl->ray.moveSpeed)] == '0')
			ctrl->ray.pos.y += ctrl->ray.dir.y * ctrl->ray.moveSpeed;
	}
	if (ctrl->move.x == -1)
	{
		if (ctrl->map[(int)(ctrl->ray.pos.x - ctrl->ray.dir.x
				* ctrl->ray.moveSpeed)][(int)ctrl->ray.pos.y] == '0')
			ctrl->ray.pos.x -= ctrl->ray.dir.x * ctrl->ray.moveSpeed;
		if (ctrl->map[(int)ctrl->ray.pos.x][(int)(ctrl->ray.pos.y
			- ctrl->ray.dir.y * ctrl->ray.moveSpeed)] == '0')
			ctrl->ray.pos.y -= ctrl->ray.dir.y * ctrl->ray.moveSpeed;
	}
}

/**
 * @brief Gestion des actions : gauche et droite
 * 
 * @param ctrl 
 */
void	move_right_left(t_ctrl *ctrl)
{
	if (ctrl->move.y == 1)
	{
		if (ctrl->map[(int)(ctrl->ray.pos.x + ctrl->ray.dir.y
				* (ctrl->ray.moveSpeed))][(int)ctrl->ray.pos.y] == '0')
			ctrl->ray.pos.x += ctrl->ray.dir.y * ctrl->ray.moveSpeed / 2;
		if (ctrl->map[(int)ctrl->ray.pos.x][(int)(ctrl->ray.pos.y
			- ctrl->ray.dir.x * (ctrl->ray.moveSpeed))] == '0')
			ctrl->ray.pos.y -= ctrl->ray.dir.x * ctrl->ray.moveSpeed / 2;
	}
	if (ctrl->move.y == -1)
	{
		if (ctrl->map[(int)(ctrl->ray.pos.x - ctrl->ray.dir.y
				* (ctrl->ray.moveSpeed))][(int)ctrl->ray.pos.y] == '0')
			ctrl->ray.pos.x -= ctrl->ray.dir.y * ctrl->ray.moveSpeed / 2;
		if (ctrl->map[(int)ctrl->ray.pos.x][(int)(ctrl->ray.pos.y
			+ ctrl->ray.dir.x * (ctrl->ray.moveSpeed))] == '0')
			ctrl->ray.pos.y += ctrl->ray.dir.x * ctrl->ray.moveSpeed / 2;
	}
}

void	move_rotate_left(t_ctrl *ctrl, double old_dir_x, double old_plane_x)
{
	if (ctrl->rotate == -1)
	{
		ctrl->ray.dir.x = old_dir_x * cos(ctrl->ray.rotSpeed)
			- ctrl->ray.dir.y * sin(ctrl->ray.rotSpeed);
		ctrl->ray.dir.y = old_dir_x * sin(ctrl->ray.rotSpeed)
			+ ctrl->ray.dir.y * cos(ctrl->ray.rotSpeed);
		ctrl->ray.plane.x = old_plane_x * cos(ctrl->ray.rotSpeed)
			- ctrl->ray.plane.y * sin(ctrl->ray.rotSpeed);
		ctrl->ray.plane.y = old_plane_x * sin(ctrl->ray.rotSpeed)
			+ ctrl->ray.plane.y * cos(ctrl->ray.rotSpeed);
	}
}

/**
 * @brief Gesion des action : tourner la camera vers la gauche et la droite
 * 
 * @param ctrl 
 */
void	move_rotate_right_left(t_ctrl *ctrl)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = ctrl->ray.dir.x;
	old_plane_x = ctrl->ray.plane.x;
	if (ctrl->rotate == 1)
	{
		ctrl->ray.dir.x = old_dir_x * cos(-ctrl->ray.rotSpeed)
			- ctrl->ray.dir.y * sin(-ctrl->ray.rotSpeed);
		ctrl->ray.dir.y = old_dir_x * sin(-ctrl->ray.rotSpeed)
			+ ctrl->ray.dir.y * cos(-ctrl->ray.rotSpeed);
		ctrl->ray.plane.x = old_plane_x * cos(-ctrl->ray.rotSpeed)
			- ctrl->ray.plane.y * sin(-ctrl->ray.rotSpeed);
		ctrl->ray.plane.y = old_plane_x * sin(-ctrl->ray.rotSpeed)
			+ ctrl->ray.plane.y * cos(-ctrl->ray.rotSpeed);
	}
	move_rotate_left(ctrl, old_dir_x, old_plane_x);
}
