#include "cub3d.h"

/*
** 함수 render_next_frame : 이 함수에 들어 있는 함수 순서대로 윈도우 화면에
** 랜더링을 시작한다.
*/

int     render_next_frame(t_win *w)
{
	draw_background(w);
	cast_rays(w);
	return (0);
}

int				shut_down(t_win *w)
{
	exit(0);
}

/*
** 함수 key_press : 이 함수를 통해 플레이어가 움직이는 것을 알려준다.
*/

int				key_press(int keycode, t_win *w)
{
	int color;
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

void				init_window(t_win *w)
{
	// 1. mlx 관련 함수 시작
	w->mlx = mlx_init();
	w->wall.height = 600;
	w->player.width = w->wall.length / 3;
	// 2. map parsing
	map_init(w);
	// 3. player setting
	init_player_ang(w);
	w->player.height = w->R_height / 2;
	// 3. 해상도 설정
	w->fov_ang = M_PI / 3;
	w->player.projected_plane = w->R_width * 0.5 * atan(w->fov_ang * 0.5);
	// 4. 윈도우 창의 크기 설정
	w->win = mlx_new_window(w->mlx, w->R_width, w->R_height, "cub3D");
	// 5. 윈도우에 넣을 이미지 크기 정하기
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

int					main(int argc, char **argv)
{
	t_win			w;
	int				save_opt;

	save_opt = (argc == 2 && (ft_memcmp(argv[argc - 1], "--save", 6) == 0));
	printf("save_opt : %d\n", save_opt);
	w.wall.length = 150;
	file_parser(&w, argv[1]);
	init_struct_win(&w);
	if (save_opt == 1)
		return(screenshot(&w));
	mlx_hook(w.win, 2, 0, key_press, &w);
	mlx_hook(w.win, 17, 0, shut_down, &w);
	mlx_loop_hook(w.mlx, render_next_frame, &w);
	mlx_loop(w.mlx);

	return (0);
}
