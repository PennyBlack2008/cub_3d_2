/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:17:57 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 21:22:39 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 함수 render_next_frame : 이 함수에 들어 있는 함수 순서대로 윈도우 화면에
** 랜더링을 시작한다.
*/

int					render_next_frame(t_win *w)
{
	draw_background(w);
	cast_rays(w);
	return (0);
}

/*
** 함수 key_press : 이 함수를 통해 플레이어가 움직이는 것을 알려준다.
*/

int					key_press(int keycode, t_win *w)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(w->mlx, w->img.ptr);
		mlx_destroy_window(w->mlx, w->win);
		exit(0);
	}
	if (keycode == KEY_W)
		move_forward(w);
	if (keycode == KEY_A)
		move_left(w);
	if (keycode == KEY_S)
		move_back(w);
	if (keycode == KEY_D)
		move_right(w);
	if (keycode == KEY_LEFT)
		rotate_left(w);
	if (keycode == KEY_RIGHT)
		rotate_right(w);
	return (0);
}

int					main(int argc, char **argv)
{
	t_win			w;
	int				save_opt;

	save_opt = (argc == 3 && (ft_memcmp(argv[argc - 1], "--save", 6) == 0));
	w.wall.length = 150;
	file_parser(&w, argv[1]);
	init_struct_win(&w);
	if (save_opt == 1)
		return (screenshot(&w));
	mlx_hook(w.win, 2, 0, key_press, &w);
	mlx_hook(w.win, 17, 0, shut_down, &w);
	mlx_loop_hook(w.mlx, render_next_frame, &w);
	mlx_loop(w.mlx);
	return (0);
}
