#include "cub_21.h"

/*
** 함수 render_next_frame : 이 함수에 들어 있는 함수 순서대로 윈도우 화면에 랜더링을 시작한다.
*/

int     render_next_frame(t_win *w)
{
	draw_background(w);
	draw_map(w);
	draw_player(w);
	cast_rays(w);
	return (0);
}

/*
** 함수 key_press : 이 함수를 통해 플레이어가 움직이는 것을 알려준다.
*/
int				key_press(int keycode, t_win *w)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(w->mlx, w->img.ptr);
		mlx_destroy_window(w->mlx, w->win);
		exit(1);
	}
	if (keycode == KEY_W)
		move_forward(w);
	if (keycode == KEY_A) // 왼쪽으로
		move_left(w);
	if (keycode == KEY_S) // 밑으로
		move_back(w);
	if (keycode == KEY_D) // 오른쪽으로
		move_right(w);
	if (keycode == KEY_LEFT) // 각도 왼쪽으로
		rotate_left(w);
	if (keycode == KEY_RIGHT) // 각도 오른쪽으로
		rotate_right(w);

	return (0);
}

void				init_window(t_win *w)
{
	// 1. mlx 관련 함수 시작
	w->mlx = mlx_init();

	// 2. 해상도 설정
	w->R_width = WIN_WIDTH;
	w->R_height = WIN_HEIGHT;
	w->aspect_ratio = w->R_height / w->R_width;
	w->fov_ang = M_PI / 3;
	w->player.projected_plane = w->R_width / 2 * atan(w->fov_ang / 2);

	// 3. 윈도우 창의 크기 설정
	w->win = mlx_new_window(w->mlx, w->R_width, w->R_height, "veryluckymanjinwoo");

	// 4. 윈도우에 넣을 이미지 크기 정하기
	w->img.ptr = mlx_new_image(w->mlx, w->R_width, w->R_height);
	w->img.addr = mlx_get_data_addr(w->img.ptr, &w->img.bits_per_pixel, &w->img.line_length, &w->img.endian);
	// -> 이미지의 위치
	w->img.x = 0;
	w->img.y = 0; 

	// 5. 벽의 크기와 높이 설정
	w->wall.length = 100;
	w->wall.height = 600;

}

void				init_player(t_win *w)
{
	// 7. player
	w->player.width = w->wall.length / 3;
	w->player.height = 500;
	w->player.ang = 0 * M_PI / 180;
	// -> player 위치
	w->player.x = 1.5 * w->wall.length;
	w->player.y = 2 * w->wall.length;
}

void				init_texture(t_win *w)
{
	// 9. texture
	int				i;
	int				j;
	int				k;

	w->tex[0].ptr = mlx_xpm_file_to_image(w->mlx, "./texture/wall_1.xpm", &w->tex[k].width, &w->tex[k].height);
	w->tex[1].ptr = mlx_xpm_file_to_image(w->mlx, "./texture/wall_2.xpm", &w->tex[k].width, &w->tex[k].height);
	w->tex[2].ptr = mlx_xpm_file_to_image(w->mlx, "./texture/wall_3.xpm", &w->tex[k].width, &w->tex[k].height);
	w->tex[3].ptr = mlx_xpm_file_to_image(w->mlx, "./texture/wall_4.xpm", &w->tex[k].width, &w->tex[k].height);
	w->tex[4].ptr = mlx_xpm_file_to_image(w->mlx, "./texture/pillar.xpm", &w->tex[k].width, &w->tex[k].height);
	k = 0;
	while (k < 5)
	{	
		w->tex[k].addr = (int *)mlx_get_data_addr(w->tex[k].ptr, &w->tex[k].bpp, &w->tex[k].len, &w->tex[k].endian);
		w->map.curr_tex[k] = (int *)ft_calloc((w->tex[k].height * w->tex[k].width), sizeof(int));
		i = 0;
		while (i < w->tex[k].height)
		{
			j = 0;
			while (j < w->tex[k].width)
			{
				w->map.curr_tex[k][(int)w->tex[k].width * i + j] = w->tex[k].addr[(int)w->tex[k].width * i + j];
				j++;
			}
			i++;
		}
		mlx_destroy_image(w->mlx, w->tex[k].ptr);
	}
}

int					init_struct_win(t_win *w)
{
	init_window(w);

	// 6. map 시작하기
	map_init(w);

	// 8. minimap
	w->mini.plot.x = w->R_width - 300;
	w->mini.plot.y = w->R_height - 300;

	// texture 및 sprite
	init_texture(w);

	return (0);
}

int main(void)
{
	t_win	w;					init_struct_win(&w);

	mlx_hook(w.win, 2, 0,key_press, &w);
	mlx_loop_hook(w.mlx, render_next_frame, &w);
	mlx_loop(w.mlx);

	return (0);
}