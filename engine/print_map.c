/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:22:26 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/29 12:34:38 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		put_pixel(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = all->imag.data + (y * all->imag.size_line + x * (all->imag.bpp / 8));
	*(unsigned int *)dst = color;
}

void		draw_pixel_texture(int x, int y, int offsetx, t_all *all)
{
	int		distancefromtop;
	int		offsety;

	distancefromtop = y + (all->cub.wall_height / 2) - (all->cub.re2 / 2);
	offsety = distancefromtop * (64.0f / all->cub.wall_height);
	if (all->cub.wallhitver[x] == 1)
	{
		if (all->cub.raydir_x[x] == 1)
			put_pixel(all, x, y, all->cub.data[3]
				[offsety * all->cub.width + offsetx]);
		else
			put_pixel(all, x, y, all->cub.data[2]
				[offsety * all->cub.width + offsetx]);
	}
	else
	{
		if (all->cub.raydir_y[x] == 1)
			put_pixel(all, x, y, all->cub.data[0]
				[offsety * all->cub.width + offsetx]);
		else
			put_pixel(all, x, y, all->cub.data[1]
				[offsety * all->cub.width + offsetx]);
	}
}

void		draw_column(int x, int offsetx, t_all *all)
{
	int y;

	y = 0;
	while (y < all->cub.re2)
	{
		if (y >= all->cub.y0 && y <= all->cub.y1)
			draw_pixel_texture(x, y, offsetx, all);
		else
		{
			if (y <= (all->cub.re2 / 2))
				put_pixel(all, x, y, all->cub.color_c);
			else
				put_pixel(all, x, y, all->cub.color_f);
		}
		y++;
	}
}

void		draw_3d(t_all *all)
{
	int		x;
	float	correctdistance;
	int		offsetx;

	x = 0;
	all->cub.dist_projectplane = (all->cub.re1 / 2) / tan(FOV / 2);
	while (x < all->cub.num_rays)
	{
		correctdistance = all->cub.raysdistance[x]
			* cos(all->cub.rays_angle[x] - all->cub.rotation_angle);
		all->cub.wall_height =
			(all->cub.size / correctdistance) * all->cub.dist_projectplane;
		all->cub.y0 = (all->cub.re2 / 2) - (all->cub.wall_height / 2);
		all->cub.y0 = all->cub.y0 < 0 ? 0 : all->cub.y0;
		all->cub.y1 = (all->cub.re2 / 2) + (all->cub.wall_height / 2);
		all->cub.y1 = all->cub.y1 > all->cub.re2 ? all->cub.re2 : all->cub.y1;
		offsetx = (int)all->cub.hitwall[x] % 64;
		draw_column(x, offsetx, all);
		x++;
	}
	sprite_correct(all);
}
