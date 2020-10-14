/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:11:49 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/29 12:34:46 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			swap(t_sprites *s1, t_sprites *s2)
{
	t_sprites	aux;

	aux = *s1;
	*s1 = *s2;
	*s2 = aux;
}

void			draw_spr_column(int x0, int y0, int y1, t_all *all)
{
	int			distancefromtop;
	int			offsety;
	int			offsetx;

	offsetx = (int)(all->j / (all->cub.wall_height / 64)) % 64;
	while (y0 < y1)
	{
		distancefromtop = y0 + (all->cub.wall_height / 2) - (all->cub.re2 / 2);
		offsety = distancefromtop * (64.0f / all->cub.wall_height);
		if (x0 >= 0 && x0 <= all->cub.re1)
		{
			if (all->cub.data[4][offsety * all->cub.width + offsetx] != 0)
				put_pixel(all, x0, y0, all->cub.data[4]
					[offsety * all->cub.width + offsetx]);
		}
		y0++;
	}
}

void			draw_sprite(int n, t_all *all)
{
	int			y0;
	int			y1;
	int			auxx;
	int			x0;
	int			x1;

	all->cub.wall_height =
		(64 / all->sprite[n].dist_s) * all->cub.dist_projectplane;
	y0 = (all->cub.re2 / 2) - (all->cub.wall_height / 2);
	y0 = y0 < 0 ? 0 : y0;
	y1 = y0 + all->cub.wall_height;
	y1 = y1 > all->cub.re2 ? all->cub.re2 : y1;
	auxx = tan(all->sprite[n].correct_angle) * all->cub.dist_projectplane;
	x0 = (all->cub.re1 / 2 - auxx) - (all->cub.wall_height / 2);
	x1 = x0 + all->cub.wall_height;
	all->j = 0;
	while (x0 < x1)
	{
		if (all->cub.raysdistance[x0] > all->sprite[n].dist_s)
			draw_spr_column(x0, y0, y1, all);
		all->j++;
		x0++;
	}
}

void			sort_sprites(t_all *all)
{
	int			i;

	i = 1;
	while (i < all->n_sprites)
	{
		if (all->sprite[i].dist_s > all->sprite[i - 1].dist_s)
		{
			swap(&all->sprite[i], &all->sprite[i - 1]);
			i = 0;
		}
		i++;
	}
	i = 0;
	while (i < all->n_sprites)
	{
		if (all->sprite[i].s_visible == 1)
			draw_sprite(i, all);
		i++;
	}
}

void			sprite_correct(t_all *all)
{
	int			i;

	i = 0;
	while (i < all->n_sprites)
	{
		all->sprite[i].vectx = all->sprite[i].sx - all->cub.pos_x;
		all->sprite[i].vecty = all->sprite[i].sy - all->cub.pos_y;
		all->sprite[i].angle_player_sprite =
			atan2(all->sprite[i].vecty, all->sprite[i].vectx);
		all->sprite[i].correct_angle =
			all->cub.rotation_angle - all->sprite[i].angle_player_sprite;
		if (all->sprite[i].correct_angle < -M_PI)
			all->sprite[i].correct_angle += 2 * M_PI;
		if (all->sprite[i].correct_angle > M_PI)
			all->sprite[i].correct_angle -= 2 * M_PI;
		if ((fabs(all->sprite[i].correct_angle)) < (45 * M_PI / 180))
			all->sprite[i].s_visible = 1;
		else
			all->sprite[i].s_visible = 0;
		all->sprite[i].dist_s = dist_between_points(all->cub.pos_x,
			all->cub.pos_y, all->sprite[i].sx, all->sprite[i].sy);
		i++;
	}
	sort_sprites(all);
}
