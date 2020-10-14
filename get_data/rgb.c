/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 13:03:05 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/14 13:59:33 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void				check_color(int j, char *tmp, char *s, t_all *all)
{
	if (((tmp[0] == 'F' && all->cub.flag_f == 1) ||
		(tmp[0] == 'C' && all->cub.flag_c == 1)))
		exit_cub("Error\nRGB duplicated\n", all);
	if (s[j + 1] != ' ' && s[j + 1] != 9)
		exit_cub("Error\nWrong RGB format\n", all);
	if (tmp[0] == 'F' && all->cub.flag_f == 0)
		all->cub.flag_f = 1;
	else if (tmp[0] == 'C' && all->cub.flag_c == 0)
		all->cub.flag_c = 1;
}

int					get_rgb_nb(int j, char *s, int *rgb, int i)
{
	int				color;
	int				flag;

	color = 0;
	flag = 0;
	while (s[j] && s[j] >= '0' && s[j] <= '9')
	{
		color = color * 10 + (s[j] - 48);
		j++;
		flag = 1;
	}
	if (flag == 1)
		rgb[i] = color;
	return (j);
}

void				get_rgb(int *rgb, char *s, t_all *all)
{
	int				j;
	int				i;

	i = 0;
	j = 1;
	while (s[j] && i < 3)
	{
		j = get_rgb_nb(j, s, rgb, i);
		if (rgb[i] > 255)
			exit_cub("Error\nRGB should be less than 255\n", all);
		if (s[j] != ',' && i < 2)
			exit_cub("Error\nWrong RGB format\n", all);
		else if (s[j] == ',' && i < 2)
			j++;
		i++;
	}
	if (s[j] != '\0')
		exit_cub("Error\nWrong RGB format\n", all);
}

void				*color(int j, char *line, char *tmp, t_all *all)
{
	int				*rgb;
	char			*s;

	check_color(j, tmp, line, all);
	s = delete_spaces(0, line);
	if (!(rgb = malloc(sizeof(int) * 3)))
		return (NULL);
	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	get_rgb(rgb, s, all);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		exit_cub("Error\nWrong RGB colors\n", all);
	if (tmp[0] == 'F')
		all->cub.color_f = 65536 * rgb[0] + 256 * rgb[1] + rgb[2];
	else if (tmp[0] == 'C')
		all->cub.color_c = 65536 * rgb[0] + 256 * rgb[1] + rgb[2];
	free(s);
	s = NULL;
	free(rgb);
	rgb = NULL;
	return (0);
}
