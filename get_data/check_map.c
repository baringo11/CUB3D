/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:37:08 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/13 14:34:43 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	find_first_position(int i, int j, t_all *all)
{
	if (all->cub.flag_first_pos == 0)
	{
		all->cub.pos_x = j * all->cub.size + (all->cub.size / 2);
		all->cub.pos_y = i * all->cub.size + (all->cub.size / 2);
		if (all->cub.mapa[i][j] == 'N')
			all->cub.rotation_angle = 270 * M_PI / 180;
		else if (all->cub.mapa[i][j] == 'S')
			all->cub.rotation_angle = 90 * M_PI / 180;
		else if (all->cub.mapa[i][j] == 'E')
			all->cub.rotation_angle = 0;
		else if (all->cub.mapa[i][j] == 'W')
			all->cub.rotation_angle = 180 * M_PI / 180;
		all->cub.flag_first_pos = 1;
	}
	else
	{
		exit_cub("Error\nMore than one initial position\n", all);
		exit(1);
	}
}

void	check_not_empty_space(int i, int j, t_all *all)
{
	if (((j == 0 || j == (all->cub.columnas - 1)) ||
		(i == 0 || i == (all->cub.filas - 1))) &&
		(all->cub.mapa[i][j] == '0' || all->cub.mapa[i][j] == '2' ||
		all->cub.mapa[i][j] == 'N' || all->cub.mapa[i][j] == 'S' ||
		all->cub.mapa[i][j] == 'W' || all->cub.mapa[i][j] == 'E'))
		exit_cub("Error\nInvalid map\n", all);
	if (all->cub.mapa[i][j] == '0' || all->cub.mapa[i][j] == '2' ||
		all->cub.mapa[i][j] == 'N' || all->cub.mapa[i][j] == 'S' ||
		all->cub.mapa[i][j] == 'W' || all->cub.mapa[i][j] == 'E')
	{
		if (all->cub.mapa[i][j - 1] == ' ' ||
			all->cub.mapa[i][j + 1] == ' ' ||
			all->cub.mapa[i - 1][j] == ' ' ||
			all->cub.mapa[i + 1][j] == ' ')
			exit_cub("Error\nInvalid map\n", all);
		if (all->cub.mapa[i - 1][j - 1] == ' ' ||
			all->cub.mapa[i - 1][j + 1] == ' ' ||
			all->cub.mapa[i + 1][j - 1] == ' ' ||
			all->cub.mapa[i + 1][j + 1] == ' ')
			exit_cub("Error\nInvalid map\n", all);
	}
}

void	validate_map(t_all *all)
{
	int i;
	int j;

	if (all->cub.flag_first_pos == 0)
		exit_cub("Error\nInitial position not found\n", all);
	i = 0;
	while (i < all->cub.filas)
	{
		j = 0;
		while (j < all->cub.columnas)
		{
			check_not_empty_space(i, j, all);
			j++;
		}
		i++;
	}
}

void	*fill_map_matrix(int i, int j, int k, t_all *all)
{
	while (i < all->cub.filas)
	{
		if (!(all->cub.mapa[i] = malloc(1 * (all->cub.columnas + 1))))
			return (NULL);
		j = 0;
		while (all->cub.map[k] != '\n' && all->cub.map[k] != '\0')
		{
			all->cub.mapa[i][j] = all->cub.map[k];
			if (all->cub.map[k] != '1' && all->cub.map[k] != '0' &&
				ft_strchr("NSEW", all->cub.mapa[i][j]))
				find_first_position(i, j, all);
			if (all->cub.map[k] == '2')
			{
				all->sprite[all->j].sx = j * 64 + (64 / 2);
				all->sprite[all->j].sy = i * 64 + (64 / 2);
				all->j++;
			}
			j++;
			k++;
		}
		k++;
		fill_spaces(i, j, all);
		i++;
	}
	return (0);
}

void	*mapa(t_all *all)
{
	int k;

	if (!all->cub.map)
		exit_cub("Error\nMap doesn't exits\n", all);
	k = 0;
	while (all->cub.map[k])
	{
		if (all->cub.map[k] == '2')
			all->n_sprites++;
		k++;
	}
	if (all->n_sprites != 0 &&
	(((k = open(all->cub.textures[4], O_RDONLY)) < 0) || !all->cub.textures[4]))
	{
		close(k);
		exit_cub("Error\nSprite texture not found\n", all);
	}
	if (!(all->sprite =
		(t_sprites *)malloc(sizeof(t_sprites) * all->n_sprites)))
		return (NULL);
	if (!(all->cub.mapa = (char **)malloc(sizeof(char *) * (all->cub.filas))))
		return (NULL);
	fill_map_matrix(0, 0, 0, all);
	validate_map(all);
	return (0);
}
