/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 14:53:13 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 13:30:30 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_step_side_dist(t_ray *ray)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (ray->pos.x - ray->map.x) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (ray->pos.y - ray->map.y) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->deltaDist.y;
	}
}

void	calcul_dda(t_ctrl *ctrl)
{
	t_ray	*ray;

	ray = &ctrl->ray;
	while (1)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (ctrl->map[ray->map.x][ray->map.y] == '1')
			break ;
	}
}

void	ft_draw_line(t_ctrl *ctrl)
{
	int	j;

	j = 0;
	while (j < ctrl->ray.drawStart)
	{
		ctrl->win.img.addr[j * ctrl->win.img.size_line / 4 + ctrl->ray.x]
			= rgbtohexa(ctrl->c_colors[0], ctrl->c_colors[1],
				ctrl->c_colors[2]);
		j++;
	}
	ft_get_dir(ctrl, j);
	j = ctrl->ray.drawEnd;
	while (j < ctrl->win.win_coord.y)
	{
		ctrl->win.img.addr[j * ctrl->win.img.size_line / 4 + ctrl->ray.x]
			= rgbtohexa(ctrl->f_colors[0], ctrl->f_colors[1],
				ctrl->f_colors[2]);
		j++;
	}
}

void	ft_draw_start_end(t_ctrl *ctrl, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = ray->sideDist.x - ray->deltaDist.x;
	else
		ray->perpWallDist = ray->sideDist.y - ray->deltaDist.y;
	ray->lineHeight = (int)(ctrl->win.win_coord.y / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + ctrl->win.win_coord.y / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + ctrl->win.win_coord.y / 2;
	if (ray->drawEnd >= ctrl->win.win_coord.y || ray->drawEnd < 0)
		ray->drawEnd = ctrl->win.win_coord.y - 1;
}

/**
 * @brief 
 * 
 * @param ctrl 
 * @return int 
 */
int	ft_raycasting(t_ctrl *ctrl)
{
	t_ray	*ray;

	ft_init_ray(ctrl);
	ray = &ctrl->ray;
	while (ray->x < ctrl->win.win_coord.x)
	{
		ft_reset_ray(ray, ctrl->win.win_coord.x);
		init_delta_dist(ray);
		calculate_step_side_dist(ray);
		calcul_dda(ctrl);
		ft_draw_start_end(ctrl, ray);
		ft_draw_line(ctrl);
		ray->x++;
	}
	mlx_put_image_to_window(ctrl->win.mlx_ptr, ctrl->win.win_ptr,
		ctrl->win.img.ptr, 0, 0);
	move_forward_backward(ctrl);
	move_right_left(ctrl);
	move_rotate_right_left(ctrl);
	return (0);
}
