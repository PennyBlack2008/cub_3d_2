#include "cub_21.h"

int					draw_player(t_win *w)
{
	int width, height;
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;
	
	width = w->player.width;
	height = w->player.height;

	// 돌리는 건 성공했는 데, 애초에 사각형의 끝점을 중심으로 그렸기 때문에 내가 원하는 공식을 쓸 수가 없다.
	x = width / 2 * -1;
	while (x < width/2)
	{
		y = width / 2 * -1;
		while (y < width / 2)
		{
			plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
			plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
			plot_player.x = plot.x + w->player.x;
			plot_player.y = plot.y + w->player.y;
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0xbbccff);
				// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
			}
			y++;
		}
		x++;
	}
	// 정면 작대기
	x = 0;
	while (x < width / 2 + 30)
	{
		y = 0;
		plot.x = x * cos(w->player.ang * -1) + y * sin(w->player.ang * -1);
		plot.y = x * sin(w->player.ang * -1) * -1 + y * cos(w->player.ang * -1);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0xFF0000);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		x++;
	}

	// 우측 작대기
	y = 0;
	while (y < height / 2 + 30)
	{
		x = 0;
		plot.x = -1 * y * sin(w->player.ang);
		plot.y = y * cos(w->player.ang);
		plot_player.x = plot.x + w->player.x;
		plot_player.y = plot.y + w->player.y;
		if (plot_player.x >= 0 && plot_player.y >= 0)
		{
			my_mlx_pixel_put(&w->img, plot_player.x, plot_player.y, 0x0000FF);
			// printf("%d %d\n", round_num_AND_int(plot_player.x), round_num_AND_int(plot_player.y));
		}
		y++;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);

	return (0);
}
