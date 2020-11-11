/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:19:18 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 21:19:34 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)n;
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
}

static int	write_bmp_header(int fd, int file_size, t_win *w)
{
	int				ret;
	unsigned char	bmp_header[54];

	ft_bzero(bmp_header, 54);
	ft_memcpy(bmp_header, "BM", sizeof(char) * 2);
	int_to_char(file_size, bmp_header + 2);
	bmp_header[10] = (unsigned char)54;
	bmp_header[14] = (unsigned char)40;
	int_to_char(w->R_width, bmp_header + 18);
	int_to_char(w->R_height, bmp_header + 22);
	bmp_header[26] = (unsigned char)1;
	bmp_header[28] = (unsigned char)24;
	ret = write(fd, bmp_header, 54);
	return (ret);
}

static int	get_color(t_win *w, int x, int y)
{
	int			color;
	int			rgb;

	color = my_mlx_pixel_get(&w->img, x, y);
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int	write_bmp_data(int fd, int pad, t_win *w)
{
	int				i;
	int				j;
	int				color;
	unsigned char	zero[3];

	i = -1;
	while (++i < 3)
		zero[i] = 0;
	i = w->R_height + 1;
	while (--i > 0)
	{
		j = -1;
		while (++j < w->R_width)
		{
			color = get_color(w, j, i);
			if (write(fd, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(fd, &zero, pad) < 0)
				return (0);
		}
	}
	return (1);
}

int			screenshot(t_win *w)
{
	int		fd;
	int		file_size;
	int		pixel_bytes_per_row;
	int		pad;

	cast_rays(w);
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	pixel_bytes_per_row = w->R_width * 3;
	pad = (4 - pixel_bytes_per_row % 4) % 4;
	file_size = 14 + 40 + 3 * (w->R_width + pad) * w->R_height;
	if ((fd = open("screenshot.bmp", O_RDWR | O_CREAT | O_TRUNC, 0644)) < 0)
		return (0);
	if (!(write_bmp_header(fd, file_size, w)) ||
			!(write_bmp_data(fd, pad, w)))
		return (0);
	close(fd);
	return (1);
}
