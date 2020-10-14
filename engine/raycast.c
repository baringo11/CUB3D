/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 13:03:02 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/22 13:25:44 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	dir_ray(int i, t_all *all)
{
	if (all->cub.ray_angle > 0 && all->cub.ray_angle < M_PI)
		all->cub.raydir_y[i] = 1;
	else
		all->cub.raydir_y[i] = -1;
	if (all->cub.ray_angle < (0.5 * M_PI) || all->cub.ray_angle > (1.5 * M_PI))
		all->cub.raydir_x[i] = 1;
	else
		all->cub.raydir_x[i] = -1;
}

void	normalizar_rayangle(t_all *all)
{
	if (all->cub.ray_angle >= 360 * (M_PI / 180))
		all->cub.ray_angle = all->cub.ray_angle - (2 * M_PI);
	if (all->cub.ray_angle < 0)
		all->cub.ray_angle = (2 * M_PI) + all->cub.ray_angle;
}

void	put_rays_dist(int i, t_all *all)
{
	if (all->cub.dist_verwallhit < all->cub.dist_horwallhit)
	{
		all->cub.dist_wall = all->cub.dist_verwallhit;
		all->cub.wallhitver[i] = 1;
		all->cub.hitwall[i] = all->cub.hit_very;
	}
	else
	{
		all->cub.dist_wall = all->cub.dist_horwallhit;
		all->cub.wallhitver[i] = 0;
		all->cub.hitwall[i] = all->cub.hit_horx;
	}
}

void	raycast(t_all *all)
{
	int	i;

	all->cub.ray_angle = all->cub.rotation_angle - (FOV / 2);
	i = 0;
	while (i < all->cub.num_rays)
	{
		normalizar_rayangle(all);
		dir_ray(i, all);
		horizontal_inter(i, all);
		vertical_inter(i, all);
		put_rays_dist(i, all);
		all->cub.raysdistance[i] = all->cub.dist_wall;
		all->cub.rays_angle[i] = all->cub.ray_angle;
		i++;
		all->cub.ray_angle += FOV / all->cub.re1;
	}
}
