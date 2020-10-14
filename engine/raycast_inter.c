/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 11:39:46 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/22 13:24:15 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			hit_wall(double y, double x, t_all *all)
{
	int map_y;
	int map_x;

	map_y = (int)(y / all->cub.size);
	map_x = (int)(x / all->cub.size);
	if (all->cub.mapa[map_y][map_x] == '1')
		return (1);
	else if (all->cub.mapa[map_y][map_x] == '2')
		return (2);
	return (0);
}

void		horizontal_inter_2(int wallhit_hor, double hor_xintercept,
			double hor_yintercept, t_all *all)
{
	if (wallhit_hor == 1)
		all->cub.dist_horwallhit = dist_between_points(all->cub.pos_x,
			all->cub.pos_y, hor_xintercept, hor_yintercept);
	else
		all->cub.dist_horwallhit = MAXFLOAT;
	all->cub.hit_horx = hor_xintercept;
	all->cub.hit_hory = hor_yintercept;
}

void		horizontal_inter(int i, t_all *all)
{
	double	hor_yintercept;
	double	hor_xintercept;
	double	hor_ystep;
	double	hor_xstep;
	int		wallhit_hor;

	hor_yintercept = (int)(all->cub.pos_y / all->cub.size) * all->cub.size;
	hor_yintercept += (all->cub.raydir_y[i] == 1) ? all->cub.size : 0;
	hor_xintercept = all->cub.pos_x +
		((hor_yintercept - all->cub.pos_y) / tan(all->cub.ray_angle));
	hor_ystep = all->cub.size * all->cub.raydir_y[i];
	hor_xstep = all->cub.size / tan(all->cub.ray_angle);
	hor_xstep *= (all->cub.raydir_x[i] == -1 && hor_xstep > 0) ? -1 : 1;
	hor_xstep *= (all->cub.raydir_x[i] == 1 && hor_xstep < 0) ? -1 : 1;
	wallhit_hor = 0;
	while (wallhit_hor != 1 && hor_yintercept > 0 && hor_xintercept > 0 &&
		hor_yintercept < (all->cub.filas * all->cub.size) &&
		hor_xintercept < (all->cub.columnas * all->cub.size))
	{
		wallhit_hor = hit_wall(hor_yintercept +
			((all->cub.raydir_y[i] == -1) ? -1 : 0), hor_xintercept, all);
		hor_yintercept += wallhit_hor != 1 ? hor_ystep : 0;
		hor_xintercept += wallhit_hor != 1 ? hor_xstep : 0;
	}
	horizontal_inter_2(wallhit_hor, hor_xintercept, hor_yintercept, all);
}

void		vertical_inter_2(int wallhit_ver, double ver_xintercept,
			double ver_yintercept, t_all *all)
{
	if (wallhit_ver == 1)
		all->cub.dist_verwallhit = dist_between_points(all->cub.pos_x,
			all->cub.pos_y, ver_xintercept, ver_yintercept);
	else
		all->cub.dist_verwallhit = MAXFLOAT;
	all->cub.hit_verx = ver_xintercept;
	all->cub.hit_very = ver_yintercept;
}

void		vertical_inter(int i, t_all *all)
{
	double	ver_xintercept;
	double	ver_yintercept;
	double	ver_xstep;
	double	ver_ystep;
	int		wallhit_ver;

	ver_xintercept = (int)(all->cub.pos_x / all->cub.size) * all->cub.size;
	ver_xintercept += (all->cub.raydir_x[i] == 1) ? all->cub.size : 0;
	ver_yintercept = all->cub.pos_y +
		((ver_xintercept - all->cub.pos_x) * tan(all->cub.ray_angle));
	ver_xstep = all->cub.size * all->cub.raydir_x[i];
	ver_ystep = all->cub.size * tan(all->cub.ray_angle);
	ver_ystep *= (all->cub.raydir_y[i] == -1 && ver_ystep > 0) ? -1 : 1;
	ver_ystep *= (all->cub.raydir_y[i] == 1 && ver_ystep < 0) ? -1 : 1;
	wallhit_ver = 0;
	while (wallhit_ver != 1 && ver_yintercept > 0 && ver_xintercept > 0 &&
		ver_yintercept < (all->cub.filas * all->cub.size) &&
		ver_xintercept < (all->cub.columnas * all->cub.size))
	{
		wallhit_ver = hit_wall(ver_yintercept, ver_xintercept +
			((all->cub.raydir_x[i] == -1) ? -1 : 0), all);
		ver_yintercept += wallhit_ver != 1 ? ver_ystep : 0;
		ver_xintercept += wallhit_ver != 1 ? ver_xstep : 0;
	}
	vertical_inter_2(wallhit_ver, ver_xintercept, ver_yintercept, all);
}
