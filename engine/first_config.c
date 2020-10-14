/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 12:41:57 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/14 14:01:30 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	prox_vel(t_all *all)
{
	if (all->cub.re1 > 2000)
		all->cub.move_speed = ((float)all->cub.size / 2);
	else if (all->cub.re1 >= 700 && all->cub.re1 <= 2000)
		all->cub.move_speed = ((float)all->cub.size / 4);
	else if (all->cub.re1 < 700)
		all->cub.move_speed = ((float)all->cub.size / 6);
	if (all->cub.re2 < 700)
		all->cub.rotation_speed = 1.5 * M_PI / 180;
}

void	*first_config(t_all *all)
{
	new_wind(all);
	set_texture_ptr(all);
	all->cub.num_rays = all->cub.re1;
	if (!(all->cub.raysdistance = malloc(sizeof(double) * all->cub.num_rays)))
		return (NULL);
	if (!(all->cub.rays_angle = malloc(sizeof(double) * all->cub.num_rays)))
		return (NULL);
	if (!(all->cub.wallhitver = malloc(sizeof(int) * all->cub.num_rays)))
		return (NULL);
	if (!(all->cub.raydir_x = malloc(sizeof(int) * all->cub.num_rays)))
		return (NULL);
	if (!(all->cub.raydir_y = malloc(sizeof(int) * all->cub.num_rays)))
		return (NULL);
	if (!(all->cub.hitwall = malloc(sizeof(double) * all->cub.num_rays)))
		return (NULL);
	prox_vel(all);
	raycast(all);
	draw_3d(all);
	if (all->cub.flag_save == 1)
		create_bitmap(all);
	mlx_put_image_to_window(all->imag.init,
		all->imag.win, all->imag.image, 0, 0);
	return (0);
}

int		key_press(int keycode, t_all *all)
{
	if (keycode == KEY_W)
	{
		all->cub.walkdir = 1;
		all->cub.flag_move = 1;
	}
	if (keycode == KEY_S)
	{
		all->cub.walkdir = -1;
		all->cub.flag_move = -1;
	}
	if (keycode == KEY_D || keycode == KEY_A)
	{
		all->cub.walkdir = 1;
		if (keycode == KEY_D)
			all->cub.walkperp = 90 * (M_PI / 180);
		else
			all->cub.walkperp = -90 * (M_PI / 180);
	}
	if (keycode == KEY_RIGHT_ARROW)
		all->cub.rotation_dir = 1;
	if (keycode == KEY_LEFT_ARROW)
		all->cub.rotation_dir = -1;
	if (keycode == KEY_ESC)
		exit_cub("", all);
	return (0);
}

int		key_release(int keycode, t_all *all)
{
	if (keycode == KEY_W || keycode == KEY_S)
	{
		all->cub.walkdir = 0;
		all->cub.flag_move = 0;
	}
	if (keycode == KEY_D || keycode == KEY_A)
	{
		if (!all->cub.flag_move)
			all->cub.walkdir = 0;
		if (all->cub.flag_move == -1)
			all->cub.walkdir = -1;
		all->cub.walkperp = 0;
	}
	if (keycode == KEY_RIGHT_ARROW)
		all->cub.rotation_dir = 0;
	else if (keycode == KEY_LEFT_ARROW)
		all->cub.rotation_dir = 0;
	return (0);
}

int		main_loop(t_all *all)
{
	if (all->cub.walkdir || all->cub.rotation_dir)
	{
		new_wind(all);
		movement(all);
		mlx_clear_window(all->imag.init, all->imag.win);
		mlx_put_image_to_window(
			all->imag.init, all->imag.win, all->imag.image, 0, 0);
	}
	return (0);
}
