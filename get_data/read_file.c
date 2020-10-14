/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:10:29 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/14 14:01:52 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		png_to_xpm(int i, t_all *all)
{
	char	*tmp;

	tmp = png_texture(all->cub.textures[i]);
	free(all->cub.textures[i]);
	all->cub.textures[i] = tmp;
}

void		check_textures(int i, char *line, t_all *all)
{
	int		fd;

	free(line);
	line = NULL;
	while (i < 4)
	{
		if (i < 4 && !all->cub.textures[i])
			exit_cub("Error\nNot enough textures\n", all);
		png_to_xpm(i, all);
		if ((fd = open(all->cub.textures[i], O_RDONLY)) < 0)
		{
			close(fd);
			exit_cub("Error\nCan't open textures\n", all);
		}
		else
			close(fd);
		i++;
	}
	if (all->cub.textures[i] != NULL)
		png_to_xpm(i, all);
	if (!all->cub.re1 || !all->cub.re2)
		exit_cub("Error\nResolution not found\n", all);
	if (all->cub.flag_c == 0 || all->cub.flag_f == 0)
		exit_cub("Error\nWrong RGB\n", all);
}

void		resolucion2(double re1, double re2, t_all *all)
{
	if (re1 > 2147483647 || re2 > 2147483647)
		exit_cub("Error\nMax Int resolution\n", all);
	all->cub.re1 = (int)re1;
	all->cub.re2 = (int)re2;
	if (re1 > 2610)
		all->cub.re1 = 2610;
	if (re2 > 1440)
		all->cub.re2 = 1440;
}

void		resolucion(int j, char *line, t_all *all)
{
	double re1;
	double re2;

	re1 = 0;
	re2 = 0;
	j++;
	while (line[j] == ' ' || line[j] == 9)
		j++;
	while (line[j] >= '0' && line[j] <= '9')
	{
		re1 = re1 * 10 + (line[j] - 48);
		j++;
	}
	while (line[j] == ' ' || line[j] == 9)
		j++;
	while (line[j] >= '0' && line[j] <= '9')
	{
		re2 = re2 * 10 + (line[j] - 48);
		j++;
	}
	while (line[j] == ' ' || line[j] == 9)
		j++;
	if (line[j] != '\0')
		exit_cub("Error\nWrong resolution\n", all);
	resolucion2(re1, re2, all);
}

void		read_file(t_all *all)
{
	int		t_read;
	int		j;
	char	*line;
	char	*tmp;

	while ((t_read = get_next_line(all->cub.fd, &line)) > 0)
	{
		j = 0;
		while (line[j] == ' ' || line[j] == 9)
			j++;
		if (line[j] == 'R')
			resolucion(j, line, all);
		else if (line[j] != 0 && (tmp = ft_strchr("NSWE", line[j])))
			texture(j, line, tmp, all);
		else if (line[j] != 0 && (tmp = ft_strchr("FC", line[j])))
			color(j, line, tmp, all);
		else if (line[j] == '1' || line[j] == '0' || line[j] == '2')
			read_map(line, all);
		if (t_read == 2)
			break ;
		free(line);
		line = NULL;
	}
	check_textures(0, line, all);
	mapa(all);
}
