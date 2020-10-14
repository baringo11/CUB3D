/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:29:22 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/13 13:05:35 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char		*special_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(s3 = malloc((ft_strlen(s1) + ft_strlen(s2)) + 2)))
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = '\n';
	i++;
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}

char		*remove_tab2(int i, int j, char *s, char *line)
{
	int		k;

	while (line[i])
	{
		k = 0;
		if (line[i] == 9)
		{
			while (line[i] == 9 && k < 4)
			{
				s[j] = ' ';
				j++;
				k++;
			}
			i++;
		}
		else
		{
			s[j] = line[i];
			i++;
			j++;
		}
	}
	s[j] = '\0';
	return (s);
}

char		*remove_tab(char *line)
{
	int		i;
	int		spaces;
	char	*s;

	i = 0;
	spaces = 0;
	while (line[i])
	{
		if (line[i] == 9)
			spaces += 3;
		i++;
	}
	if (!(s = malloc(sizeof(char) * ft_strlen(line) + spaces + 1)))
		return (NULL);
	i = 0;
	s = remove_tab2(i, 0, s, line);
	return (s);
}

void		str_map(char *line, t_all *all)
{
	char	*tmp;

	line = remove_tab(line);
	all->cub.filas++;
	if (all->cub.columnas < (int)ft_strlen(line))
		all->cub.columnas = ft_strlen(line);
	if (all->cub.map == NULL)
		all->cub.map = ft_strdup(line);
	else
	{
		tmp = special_strjoin(all->cub.map, line);
		free(all->cub.map);
		all->cub.map = tmp;
	}
	free(line);
	line = NULL;
}

void		read_map(char *line, t_all *all)
{
	int t_read;
	int j;

	str_map(line, all);
	while ((t_read = get_next_line(all->cub.fd, &line)) > 0)
	{
		j = 0;
		str_map(line, all);
		if (line[j] == '\n' || t_read == 2)
		{
			free(line);
			line = NULL;
			break ;
		}
		free(line);
		line = NULL;
	}
}
