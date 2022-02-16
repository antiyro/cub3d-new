/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 07:35:58 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/11 18:04:40 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_handle_keypress(int keysym, t_ctrl *ctrl)
{
	if (keysym == XK_Escape)
	{
		ft_freestruct(ctrl, true, SUCCESS);
		exit(0);
	}
	if (keysym == XK_w)
		ctrl->move.x = 1;
	else if (keysym == XK_s)
		ctrl->move.x = -1;
	else if (keysym == XK_a)
		ctrl->move.y = -1;
	else if (keysym == XK_d)
		ctrl->move.y = 1;
	else if (keysym == XK_Right)
		ctrl->rotate = 1;
	else if (keysym == XK_Left)
		ctrl->rotate = -1;
	return (0);
}

int	ft_handle_closetop(t_ctrl *ctrl)
{
	ft_freestruct(ctrl, true, SUCCESS);
	exit(0);
}

int	ft_handle_keyrelease(int keysym, t_ctrl *ctrl)
{
	if (keysym == XK_w)
		ctrl->move.x = 0;
	else if (keysym == XK_s)
		ctrl->move.x = 0;
	else if (keysym == XK_a)
		ctrl->move.y = 0;
	else if (keysym == XK_d)
		ctrl->move.y = 0;
	else if (keysym == XK_Right)
		ctrl->rotate = 0;
	else if (keysym == XK_Left)
		ctrl->rotate = 0;
	return (0);
}

void	ctrl_init(t_ctrl *ctrl)
{
	ctrl->move.x = 0;
	ctrl->move.y = 0;
	ctrl->rotate = 0;
	ctrl->map = NULL;
	ctrl->no_path = NULL;
	ctrl->so_path = NULL;
	ctrl->we_path = NULL;
	ctrl->ea_path = NULL;
	ctrl->f_colors = NULL;
	ctrl->c_colors = NULL;
	ctrl->ray.dir.x = 0;
	ctrl->ray.dir.y = 0;
	ctrl->ray.plane.x = 0;
	ctrl->ray.plane.y = 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	t_ctrl	ctrl;
	int		err;

	err = SUCCESS;
	if (argc != 2)
		return (ft_error(ARG, &ctrl, false));
	if (check_file(argv[1]) != SUCCESS)
		return (ft_error(FILENAME, &ctrl, false));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error(OPEN, &ctrl, false));
	ctrl_init(&ctrl);
	err = parsing(fd, &ctrl);
	close(fd);
	if (err != SUCCESS)
		return (ft_error(err, &ctrl, false));
	ft_init(&ctrl);
	mlx_hook(ctrl.win.win_ptr, 2, 1L << 0, &ft_handle_keypress, &ctrl);
	mlx_hook(ctrl.win.win_ptr, 17, 0, &ft_handle_closetop, &ctrl);
	mlx_loop_hook(ctrl.win.mlx_ptr, ft_raycasting, &ctrl);
	mlx_hook(ctrl.win.win_ptr, 3, 1L << 1, &ft_handle_keyrelease, &ctrl);
	mlx_loop(ctrl.win.mlx_ptr);
	return (0);
}
