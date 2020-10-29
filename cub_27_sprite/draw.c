#include "cub_21.h"

/*
** draw_background 함수는 검정화면을 출력하기 위한 함수입니다. 이 함수가 있어서 플레이어가 움직일 때, 움직이기 전의 위치의 픽셀을 까맣게 지워줍니다.
*/

int					draw_background(t_win *w)
{
	int				x,y;

	x = 0;
	while (x < w->R_width)
	{
		x++;
		y = 0;
		while (y < w->R_height)
		{
			my_mlx_pixel_put(&w->img, x, y, 0x000000);
			y++;
		}
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
	return (0);
}

/*
** draw_grid 는 디버깅할 때 편하려고 해상도의 가로길이와 세로길이의 반을 통과하는 선을 그리는 함수입니다.
*/

int					draw_grid(t_win *w)
{
	int x, y;

	x = 0;	y = w->R_height / 2;
	while (x < w->R_width)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		x++;
	}

	y = 0;	x = w->R_width / 2;
	while (y < w->R_height)
	{
		my_mlx_pixel_put(&w->img, x, y, 0x00ccff);
		y++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}
