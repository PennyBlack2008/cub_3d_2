#include "cub3d.h"

int					draw_player(t_win *w)
{
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang) - y * sin(w->player.ang);
			plot.y = x * sin(w->player.ang) + y * cos(w->player.ang);
			plot_player.x = plot.x + w->player.plot.x;
			plot_player.y = plot.y + w->player.plot.y;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, plot_player.y / 4 + w->mini.plot.y, 0xbbccff);
				// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
			}
			y++;
		}
		x++;
	}
	// 정면 작대기
	x = 0;
	while (x < w->player.width / 2 + 30)
	{
		y = 0;
		plot.x = x * cos(w->player.ang) - y * sin(w->player.ang);
		plot.y = x * sin(w->player.ang) + y * cos(w->player.ang);
		plot_player.x = plot.x + w->player.plot.x;
		plot_player.y = plot.y + w->player.plot.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, plot_player.y / 4 + w->mini.plot.y, 0xFF0000);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		x++;
	}

	// 우측 작대기
	y = 0;
	while (y < w->player.width / 2 + 30)
	{
		x = 0;
		plot.x = x * cos(w->player.ang) - y * sin(w->player.ang);
		plot.y = x * sin(w->player.ang) + y * cos(w->player.ang);
		plot_player.x = plot.x + w->player.plot.x;
		plot_player.y = plot.y + w->player.plot.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, plot_player.y / 4 + w->mini.plot.y, 0x0000FF);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		y++;
	}

	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}