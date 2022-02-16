/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 04:13:38 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 17:45:23 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_tex(t_ctrl *ctrl, int y, t_tex_img tex)
{
	ctrl->t.step = 1.0 * tex.height / ctrl->ray.lineHeight;
	ctrl->t.x = (int)(ctrl->t.wallx * (double)tex.width);
	ctrl->t.pos = (ctrl->ray.drawStart - ctrl->win.win_coord.y / 2
			+ ctrl->ray.lineHeight / 2) * ctrl->t.step;
	while (y <= ctrl->ray.drawEnd)
	{
		ctrl->t.y = floor(ctrl->t.pos);
		ctrl->t.pos += ctrl->t.step;
		ctrl->win.img.addr[y * ctrl->win.img.size_line / 4 + ctrl->ray.x]
			= tex.img.addr[ctrl->t.y * tex.img.size_line / 4 + ctrl->t.x];
		y++;
	}
}

void	ft_get_dir(t_ctrl *ctrl, int y)
{
	y = ctrl->ray.drawStart;
	if (ctrl->ray.side == 0)
		ctrl->t.wallx = ctrl->ray.pos.y + ctrl->ray.perpWallDist
			* ctrl->ray.rayDir.y;
	else
		ctrl->t.wallx = ctrl->ray.pos.x + ctrl->ray.perpWallDist
			* ctrl->ray.rayDir.x;
	ctrl->t.wallx -= floor(ctrl->t.wallx);
	if (ctrl->ray.side == 0 && ctrl->ray.rayDir.x < 0)
		ft_draw_tex(ctrl, y, ctrl->tex[0]);
	if (ctrl->ray.side == 0 && ctrl->ray.rayDir.x >= 0)
		ft_draw_tex(ctrl, y, ctrl->tex[1]);
	if (ctrl->ray.side == 1 && ctrl->ray.rayDir.y < 0)
		ft_draw_tex(ctrl, y, ctrl->tex[2]);
	if (ctrl->ray.side == 1 && ctrl->ray.rayDir.y >= 0)
		ft_draw_tex(ctrl, y, ctrl->tex[3]);
}

void	ft_reset_ray(t_ray *ray, int x_max)
{
	double	camera_x;

	ray->perpWallDist = 0;
	camera_x = 2 * ray->x / (double)x_max - 1;
	ray->rayDir.x = ray->dir.x + ray->plane.x * camera_x;
	ray->rayDir.y = ray->dir.y + ray->plane.y * camera_x;
	ray->map.x = (int)ray->pos.x;
	ray->map.y = (int)ray->pos.y;
}

void	init_delta_dist(t_ray *ray)
{
	if (ray->rayDir.x == 0)
		ray->deltaDist.x = 1e37;
	else
		ray->deltaDist.x = fabs(1 / ray->rayDir.x);
	if (ray->rayDir.y == 0)
		ray->deltaDist.y = 1e37;
	else
		ray->deltaDist.y = fabs(1 / ray->rayDir.y);
}
