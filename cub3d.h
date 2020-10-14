/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 10:45:33 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/13 13:46:06 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "GNL/get_next_line.h"
# include "minilibx/mlx.h"

# define FOV 1.04719755
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53
# define KEY_RIGHT_ARROW 124
# define KEY_LEFT_ARROW 123

typedef struct		s_cub
{
	int				flag_f;
	int				flag_c;
	int				flag_save;
	int				re1;
	int				re2;
	unsigned int	color_f;
	unsigned int	color_c;
	char			**textures;
	void			*imag_txt;
	int				**data;
	int				width;
	int				heigth;
	int				bpp;
	int				size_line;
	int				endian;
	int				fd;
	char			*map;
	char			**mapa;
	int				filas;
	int				columnas;
	int				size;
	double			pos_x;
	double			pos_y;
	int				movestep;
	int				walkdir;
	float			walkperp;
	int				flag_move;
	int				flag_first_pos;
	int				rotation_dir;
	double			rotation_angle;
	float			move_speed;
	double			rotation_speed;
	double			ray_angle;
	int				*raydir_y;
	int				*raydir_x;
	int				num_rays;
	double			dist_horwallhit;
	double			dist_verwallhit;
	double			dist_wall;
	double			hit_horx;
	double			hit_hory;
	double			hit_verx;
	double			hit_very;
	double			*hitwall;
	int				*wallhitver;
	double			*raysdistance;
	double			*rays_angle;
	double			dist_projectplane;
	double			wall_height;
	int				y0;
	int				y1;
}					t_cub;

typedef struct		s_imag
{
	void			*init;
	void			*win;
	void			*image;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_imag;

typedef struct		s_sprites
{
	double			sx;
	double			sy;
	double			vectx;
	double			vecty;
	double			angle_player_sprite;
	double			correct_angle;
	double			dist_s;
	int				s_visible;
}					t_sprites;

typedef struct		s_all
{
	t_cub			cub;
	t_imag			imag;
	t_sprites		*sprite;
	int				n_sprites;
	int				j;
}					t_all;

char				*png_texture(char *s);
void				fill_spaces(int i, int j, t_all *all);
char				*delete_spaces(int j, char *s);
char				*ft_strtrim(char *s1, char *set);
void				put_pixel(t_all *all, int x, int y, int color);
int					create_bitmap(t_all *all);
int					exit_cub(char *error, t_all *all);
int					ft_strcmp(char *s1, char *s2);
double				dist_between_points(double x1,
					double y1, double x2, double y2);
void				valid_argv(int argc, char **argv, t_all *all);
void				*mapa(t_all *all);
void				read_map(char *line, t_all *all);
void				*color(int j, char *line, char *tmp, t_all *all);
void				read_file(t_all *all);
void				horizontal_inter(int i, t_all *all);
void				vertical_inter(int i, t_all *all);
void				raycast(t_all *all);
void				movement(t_all *all);
void				texture(int j, char *line, char *tmp, t_all *all);
void				set_texture_ptr(t_all *all);
void				*first_config(t_all *all);
t_all				*set_init(t_all *all);
void				new_wind(t_all *all);
void				print_map(t_all *all);
int					main_loop(t_all *all);
void				sprite_correct(t_all *all);
void				draw_3d(t_all *all);
int					key_press(int keycode, t_all *all);
int					key_release(int keycode, t_all *all);

#endif
