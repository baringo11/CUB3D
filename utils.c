/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 11:59:14 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/13 14:37:05 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double		dist_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

char		*delete_spaces(int j, char *s)
{
	char	*s1;
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == 9)
			j++;
		i++;
	}
	if (!(s1 = malloc(sizeof(char) * i - j + 1)))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != 9)
		{
			s1[j] = s[i];
			j++;
		}
		i++;
	}
	s1[j] = '\0';
	return (s1);
}

char		*ft_strtrim(char *s1, char *set)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	k;

	if (s1 == NULL || set == NULL)
		return (NULL);
	j = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	if (i == j)
		return (ft_strdup(""));
	while (s1 && ft_strchr(set, s1[j]) != NULL && j != 0)
		j--;
	j -= i - 1;
	if (!(str = malloc((j + 1) * sizeof(char))))
		return (NULL);
	k = 0;
	while (k < j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}

int			ft_strcmp(char *s1, char *s2)
{
	int i;

	if (ft_strlen(s1) != ft_strlen(s2))
		return (-1);
	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void		fill_spaces(int i, int j, t_all *all)
{
	while (j < all->cub.columnas)
	{
		all->cub.mapa[i][j] = ' ';
		j++;
	}
	all->cub.mapa[i][j] = '\0';
}
