/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:21:55 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/29 13:08:10 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		normalizar_angulo(t_all *all)
{
	if (all->cub.rotation_angle >= 360 * M_PI / 180)
		all->cub.rotation_angle = all->cub.rotation_angle - (2 * M_PI);
	if (all->cub.rotation_angle < 0)
		all->cub.rotation_angle = (2 * M_PI) + all->cub.rotation_angle;
}

int			check_corner(double nextpos_x, double nextpos_y, t_all *all)
{
	int		mapx;
	int		mapy;
	int		nextmapx;
	int		nextmapy;

	mapx = all->cub.pos_x / all->cub.size;
	mapy = all->cub.pos_y / all->cub.size;
	nextmapx = nextpos_x / all->cub.size;
	nextmapy = nextpos_y / all->cub.size;
	if ((mapx == (nextmapx + 1) && mapy == (nextmapy + 1)) && all->cub.mapa
		[mapy - 1][mapx] == '1' && all->cub.mapa[mapy][mapx - 1] == '1')
		return (1);
	if ((mapx == (nextmapx - 1) && mapy == (nextmapy + 1)) && all->cub.mapa
		[mapy - 1][mapx] == '1' && all->cub.mapa[mapy][mapx + 1] == '1')
		return (1);
	if ((mapx == (nextmapx + 1) && mapy == (nextmapy - 1)) && all->cub.mapa
		[mapy][mapx - 1] == '1' && all->cub.mapa[mapy + 1][mapx] == '1')
		return (1);
	if ((mapx == (nextmapx - 1) && mapy == (nextmapy - 1)) && all->cub.mapa
		[mapy][mapx + 1] == '1' && all->cub.mapa[mapy + 1][mapx] == '1')
		return (1);
	return (0);
}

void		movement(t_all *all)
{
	double	nextpos_y;
	double	nextpos_x;
	int		flag;

	all->cub.movestep = all->cub.walkdir * all->cub.move_speed;
	all->cub.rotation_angle += all->cub.rotation_dir * all->cub.rotation_speed;
	normalizar_angulo(all);
	nextpos_x = cos(all->cub.rotation_angle + all->cub.walkperp)
		* all->cub.movestep + all->cub.pos_x;
	nextpos_y = sin(all->cub.rotation_angle + all->cub.walkperp)
		* all->cub.movestep + all->cub.pos_y;
	if ((all->cub.raysdistance[all->cub.num_rays / 2] > all->cub.movestep ||
	all->cub.walkperp != 0) && all->cub.mapa[(int)(nextpos_y / all->cub.size)]
		[(int)(nextpos_x / all->cub.size)] != '1')
	{
		flag = check_corner(nextpos_x, nextpos_x, all);
		if (flag == 0)
		{
			all->cub.pos_y = nextpos_y;
			all->cub.pos_x = nextpos_x;
		}
	}
	raycast(all);
	draw_3d(all);
}
