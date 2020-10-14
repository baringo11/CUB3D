/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 11:37:23 by jbaringo          #+#    #+#             */
/*   Updated: 2020/09/29 12:28:31 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	data_to_bitmap(t_all *all, int fd)
{
	int i;

	i = all->cub.re1 * all->cub.re2 - 1;
	while (i >= 0)
	{
		write(fd, &all->imag.data[i * all->imag.bpp / 8], 4);
		i--;
	}
	return (1);
}

static void	mir_verti_pixel(t_all *all, int line_cnt, int *e, int f)
{
	char	save;
	int		k;

	k = 3;
	while (k >= 0)
	{
		save = all->imag.data[*e + (line_cnt * all->imag.size_line)];
		all->imag.data[*e + (line_cnt * all->imag.size_line)] =
			all->imag.data[f - k + (line_cnt * all->imag.size_line - 1)];
		all->imag.data[f - k + (line_cnt * all->imag.size_line - 1)] =
			save;
		k--;
		*e = *e + 1;
	}
}

static int	mir_verti(t_all *all)
{
	int		line_cnt;
	int		e;
	int		f;

	line_cnt = 0;
	while (line_cnt < all->cub.re2)
	{
		e = 0;
		f = all->imag.size_line;
		while (e < f && e != f)
		{
			mir_verti_pixel(all, line_cnt, &e, f);
			f -= 4;
		}
		line_cnt++;
	}
	return (1);
}

static int	bitmap_info_header(t_all *all, int fd)
{
	int header_info_size;
	int plane_nbr;
	int o_count;

	header_info_size = 40;
	plane_nbr = 1;
	write(fd, &header_info_size, 4);
	write(fd, &all->cub.re1, 4);
	write(fd, &all->cub.re2, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &all->imag.bpp, 2);
	o_count = 0;
	while (o_count < 28)
	{
		write(fd, "\0", 1);
		o_count++;
	}
	return (1);
}

int			create_bitmap(t_all *all)
{
	int fd;
	int file_size;
	int first_pix;

	fd = open("cub3d.bmp", O_CREAT | O_RDWR);
	file_size = 14 + 40 + 4 + (all->cub.re1 * all->cub.re2) * 4;
	first_pix = 14 + 40 + 4;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	bitmap_info_header(all, fd);
	mir_verti(all);
	data_to_bitmap(all, fd);
	close(fd);
	all->cub.flag_save = 0;
	exit_cub("Success Screenshot\n", all);
	return (1);
}
