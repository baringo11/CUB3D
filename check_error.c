/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 13:20:32 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/28 13:36:56 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_argv(char *s)
{
	int		i;

	i = ft_strlen(s);
	if (s[i - 4] != '.' && s[i - 3] != 'c' && s[i - 2] != 'u' &&
		s[i - 1] != 'b')
		return (0);
	return (1);
}

void		valid_argv(int argc, char **argv, t_all *all)
{
	if (argc != 2 && argc != 3)
		exit_cub("Error\nWrong number of parameters\n", all);
	if (check_argv(argv[1]) == 0)
		exit_cub("Error\nMap should finish with \".cub\"\n", all);
	if ((all->cub.fd = open(argv[1], O_RDONLY)) < 0)
		exit_cub("Error\nCan't open map\n", all);
	if (argc == 3)
	{
		if ((ft_strcmp(argv[2], "--save") != 0))
		{
			exit_cub("Error\nIncorrect flag \"--save\"\n", all);
			all->cub.flag_save = 0;
		}
		else
			all->cub.flag_save = 1;
	}
}
