/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:09:27 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 21:22:01 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				init_player_ang(t_win *w)
{
	if (w->player.facing == 'N')
		w->player.ang = M_PI_2 * 3;
	else if (w->player.facing == 'S')
		w->player.ang = M_PI_2 * 1;
	else if (w->player.facing == 'E')
		w->player.ang = M_PI_2 * 0;
	else if (w->player.facing == 'W')
		w->player.ang = M_PI_2 * 2;
}

/*
** 함수: void				init_window(t_win *w)
**  1. mlx 관련 함수 시작
**  2. map parsing
**  3. 해상도 설정
**  4. 윈도우 창의 크기 설정
**  5. 윈도우에 넣을 이미지 크기 정하기
*/

void				init_window(t_win *w)
{
	w->mlx = mlx_init();
	w->wall.height = 600;
	w->player.width = w->wall.length / 3;
	map_init(w);
	init_player_ang(w);
	w->player.height = w->R_height / 2;
	w->fov_ang = M_PI / 3;
	w->player.projected_plane = w->R_width * 0.5 * atan(w->fov_ang * 0.5);
	w->win = mlx_new_window(w->mlx, w->R_width, w->R_height, "cub3D");
	w->img.ptr = mlx_new_image(w->mlx, w->R_width, w->R_height);
	w->img.addr = mlx_get_data_addr(w->img.ptr, &w->img.bits_per_pixel,
			&w->img.line_length, &w->img.endian);
	w->img.x = 0;
	w->img.y = 0;
}

void				curring_texture(int k, char *list[], t_win *w)
{
	int				i;
	int				j;

	if (!(w->tex[k].ptr = mlx_xpm_file_to_image(w->mlx, list[k],
					&w->tex[k].width, &w->tex[k].height)))
		return (error_handler("xpm file error!\n", errno));
	w->tex[k].addr = (int *)mlx_get_data_addr(w->tex[k].ptr, &w->tex[k].bpp,
			&w->tex[k].len, &w->tex[k].endian);
	w->map.curr_tex[k] = (int *)ft_calloc((w->tex[k].height *
				w->tex[k].width), sizeof(int));
	i = 0;
	while (i < w->tex[k].height)
	{
		j = 0;
		while (j < w->tex[k].width)
		{
			w->map.curr_tex[k][(int)w->tex[k].width * i + j] =
				w->tex[k].addr[(int)w->tex[k].width * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(w->mlx, w->tex[k].ptr);
}

void				init_texture(t_win *w)
{
	char			*list[5];
	int				k;

	list[0] = w->map.info.NO_texture;
	list[1] = w->map.info.SO_texture;
	list[2] = w->map.info.EA_texture;
	list[3] = w->map.info.WE_texture;
	list[4] = w->map.info.sprite_texture;
	k = 0;
	while (k < 5)
	{
		curring_texture(k, list, w);
		k++;
	}
}

int					init_struct_win(t_win *w)
{
	init_window(w);
	init_texture(w);
	return (0);
}
