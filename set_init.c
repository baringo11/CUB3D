/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:59:16 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/14 13:47:25 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_textures(t_all *all)
{
	int	i;

	if (!(all->cub.textures = (char **)malloc(sizeof(char *) * 5)))
		return (NULL);
	if (!(all->cub.data = (int **)malloc(sizeof(int *) * 5)))
		return (NULL);
	i = 0;
	while (i < 5)
	{
		all->cub.textures[i] = NULL;
		all->cub.data[i] = NULL;
		i++;
	}
	return (0);
}

t_all	*set_init(t_all *all)
{
	all->j = 0;
	all->cub.flag_f = 0;
	all->cub.flag_c = 0;
	all->cub.flag_first_pos = 0;
	all->n_sprites = 0;
	all->cub.re1 = 0;
	all->cub.re2 = 0;
	all->cub.columnas = 0;
	all->cub.filas = 0;
	all->cub.map = NULL;
	all->cub.size = 64;
	all->cub.move_speed = ((float)all->cub.size / 4);
	all->cub.rotation_speed = 3 * M_PI / 180;
	all->cub.rotation_dir = 0;
	all->cub.walkdir = 0;
	all->cub.walkperp = 0;
	all->cub.flag_move = 0;
	all->imag.init = NULL;
	all->imag.win = NULL;
	all->imag.image = NULL;
	init_textures(all);
	return (all);
}

void	new_wind(t_all *all)
{
	if (!all->imag.init || !all->imag.win)
	{
		all->imag.init = mlx_init();
		all->imag.win =
			mlx_new_window(all->imag.init, all->cub.re1, all->cub.re2, "CUB3D");
	}
	if (all->imag.image)
		mlx_destroy_image(all->imag.init, all->imag.image);
	all->imag.image = mlx_new_image(all->imag.init, all->cub.re1, all->cub.re2);
	all->imag.data =
		mlx_get_data_addr(all->imag.image, &all->imag.bpp,
			&all->imag.size_line, &all->imag.endian);
}
