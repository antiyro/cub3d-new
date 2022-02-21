/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhada <nbouhada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 07:36:30 by nbouhada          #+#    #+#             */
/*   Updated: 2022/02/14 10:34:03 by nbouhada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <mlx.h>
# include <stdbool.h>

//define errors
# define ARG 666
# define FILENAME 667
# define OPEN 668
# define HEADERROR 669
# define MAPERROR 671

//define success failure
# define SUCCESS 0
# define FAILURE 1

typedef struct	s_coordInt
{
	int	x;
	int	y;
}	t_coordInt;

typedef struct	s_coordDouble
{
	double	x;
	double	y;
}	t_coordDouble;

typedef struct	s_img
{
	void	*ptr;
	int		*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct	s_win
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_coordInt	win_coord;
	t_img		img;
}	t_win;

typedef struct	s_ray
{
	t_coordDouble	pos;
	t_coordDouble	dir;
	t_coordDouble	plane;
	t_coordDouble	rayDir;
	t_coordInt		map;
	t_coordDouble	sideDist;
	t_coordDouble	deltaDist;
	double			perpWallDist;
	t_coordInt		step;
	int				side;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	double			moveSpeed;
	double			rotSpeed;
	int				x;
}	t_ray;

typedef struct s_textures
{
	int		texdir;
	double	wallx;
	int		x;
	int		y;
	double	step;
	double	pos;
}	t_textures;

typedef struct	s_tex_img
{
	t_img	img;
	int		width;
	int		height;
}	t_tex_img;

typedef struct	s_ctrl
{
	char		**map;
	t_ray		ray;
	t_win		win;
	t_tex_img	tex[4];
	t_textures	t;
	t_coordInt	move;
	int			rotate;
	char  *no_path;
	char  *so_path;
	char  *we_path;
	char  *ea_path;
	int   *f_colors;
	int   *c_colors;
}	t_ctrl;

char			*ft_strdup(char const *s);
char			*ft_strjoin(char *s1, char *s2);
char			**ft_split(char *s, char c);
int				check_north(char *line, t_ctrl *ctrl);
int				check_south(char *line, t_ctrl *ctrl);
int				check_west(char *line, t_ctrl *ctrl);
int				check_east(char *line, t_ctrl *ctrl);
int				check_ceilling(char *line, t_ctrl *ctrl);
int				check_floor(char *line, t_ctrl *ctrl);
int				ft_strlen(char const *str);
int				ft_tablen(char **tab);
int				parsing(int fd, t_ctrl *ctrl);
int				ft_raycasting(t_ctrl *ctrl);
int				ft_init(t_ctrl *ctrl);
int				ft_init_ray(t_ctrl *ctrl);
void			move_forward_backward(t_ctrl *ctrl);
void			move_right_left(t_ctrl *ctrl);
void			move_rotate_right_left(t_ctrl *ctrl);
void			ft_get_dir(t_ctrl *ctrl, int y);
void			ft_reset_ray(t_ray *ray, int x_max);
void			init_delta_dist(t_ray *ray);
int 			check_file(char *path);
int				ft_error(int err, t_ctrl *ctrl, bool ctrlinit);
int				check_head(char **tab, t_ctrl *ctrl);
int				check_map(t_ctrl *ctrl);
int				ft_atoi(const char *str);
int				ft_is_ascii(char *str);
int 			ft_isdigit(char c);
int 			between0and255(int nb);
int 			rgbchecker(char **tab);
int 			ft_freechartab(char **tab);
void			ft_putstr_fd(char *str, int fd);
int				*tabchartotabint(char **tab);
int				check_close(int i, int j, char **map);
int				check_space_wall(char c);
int				check_character(char c);
unsigned long	rgbtohexa(int r, int g, int b);
int				ft_draw_minimap(t_ctrl *ctrl);
int				ft_freestruct(t_ctrl *ctrl, bool ctrlinit, int ret);
void			ft_free(void *content);
int				ft_fill_map(char **tab, char **map, int max_length, int l);
char			**realloc_tab(char **tab);

#endif