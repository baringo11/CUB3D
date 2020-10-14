/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:57:28 by jbaringo          #+#    #+#             */
/*   Updated: 2020/10/14 13:52:32 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_all all;

	valid_argv(argc, argv, &all);
	set_init(&all);
	read_file(&all);
	first_config(&all);
	mlx_hook(all.imag.win, 2, 0, &key_press, &all);
	mlx_hook(all.imag.win, 3, 0, &key_release, &all);
	mlx_hook(all.imag.win, 17, 0, &exit_cub, NULL);
	mlx_loop_hook(all.imag.init, &main_loop, &all);
	mlx_loop(all.imag.init);
	return (EXIT_SUCCESS);
}

int	exit_cub(char *error, t_all *all)
{
	if (error)
		write(1, error, ft_strlen(error));
	if (error)
	{
		if (all->imag.image)
			mlx_destroy_image(all->imag.init, all->imag.image);
		if (all->imag.win)
			mlx_destroy_window(all->imag.init, all->imag.win);
	}
	write(1, "** EXIT **\n", 11);
	exit(1);
}
