/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 12:53:32 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/14 12:57:34 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		set_texture_ptr(t_all *all)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		if (all->cub.textures[i])
		{
			all->cub.imag_txt = mlx_xpm_file_to_image(all->imag.init,
				all->cub.textures[i], &all->cub.width, &all->cub.heigth);
			all->cub.data[i] = (int*)mlx_get_data_addr(all->cub.imag_txt,
				&all->cub.bpp, &all->cub.size_line, &all->cub.endian);
		}
		i++;
	}
}

char		*png_texture(char *s)
{
	int		j;
	int		i;
	char	*xpm;

	j = ft_strlen(s);
	if (s[j - 4] == '.' && s[j - 3] == 'p' &&
		s[j - 2] == 'n' && s[j - 1] == 'g')
	{
		if (!(xpm = malloc(sizeof(char) * j + 1)))
			return (NULL);
		i = 0;
		while (i < (j - 3))
		{
			xpm[i] = s[i];
			i++;
		}
		xpm[i] = 'x';
		xpm[i + 1] = 'p';
		xpm[i + 2] = 'm';
		xpm[i + 3] = '\0';
		return (xpm);
	}
	return (ft_strdup(s));
}

void		path_texture(int sprite, char *line, char *tmp, t_all *all)
{
	int		j;

	j = 0;
	while (line[j] == ' ' || line[j] == 9)
		j++;
	while (line[j] != ' ')
		j++;
	while (line[j] == ' ' || line[j] == 9)
		j++;
	if (tmp[0] == 'N' && !all->cub.textures[0])
		all->cub.textures[0] = ft_strtrim(&line[j], " 	");
	else if (tmp[0] == 'S' && sprite == 0 && !all->cub.textures[1])
		all->cub.textures[1] = ft_strtrim(&line[j], " 	");
	else if (tmp[0] == 'E' && !all->cub.textures[2])
		all->cub.textures[2] = ft_strtrim(&line[j], " 	");
	else if (tmp[0] == 'W' && !all->cub.textures[3])
		all->cub.textures[3] = ft_strtrim(&line[j], " 	");
	else if (tmp[0] == 'S' && sprite == 1 && !all->cub.textures[4])
		all->cub.textures[4] = ft_strtrim(&line[j], " 	");
	else
		exit_cub("Error\nDuplicate texture\n", all);
}

void		texture(int j, char *line, char *tmp, t_all *all)
{
	int		sprite;

	sprite = 0;
	if (line[j] == 'S' && line[j + 1] != 'O')
		sprite = 1;
	if ((line[j] == 'N' && line[j + 1] == 'O') ||
		(line[j] == 'E' && line[j + 1] == 'A') ||
		(line[j] == 'W' && line[j + 1] == 'E') ||
		(line[j] == 'S' && line[j + 1] == 'O' && sprite != 1) ||
		(line[j] == 'S' && sprite == 1 && line[j + 1] == ' '))
	{
		if (sprite != 1 && line[j + 2] != ' ')
			exit_cub("Error\nWrong texture format\n", all);
		path_texture(sprite, line, tmp, all);
	}
	else
		exit_cub("Error\nWrong texture format\n", all);
}
