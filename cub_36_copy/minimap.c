#include "cub_21.h"

void				draw_minimap(t_ray *r, t_win *w)
{
	int	i;
	t_plot player;
	t_plot ray;
	
	// 미니맵 그리기
	draw_map(w);
	draw_player(w);
	set_plot(&player, (w->player.x / 4) + w->mini.plot.x, (w->player.y / 4) + w->mini.plot.y);
	i = 0;
	while (i < w->R_width)
	{
		set_plot(&ray, (r[i].hit.x / 4) + w->mini.plot.x, (r[i].hit.y / 4) + w->mini.plot.y);
		// printf("r[i].hit.x = %f, r[i].wall.x = %f\n", r[i].hit.x, r[i].wall.x);
		draw_line(player, ray, 0xFF0000, w);
		i++;
	}
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
