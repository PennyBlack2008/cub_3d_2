#include "cub3d.h"

int					draw_player(t_win *w)
{
	int	x, y;
	t_plot	plot;
	t_plot	plot_player;

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
				my_mlx_pixel_put(&w->img, plot_player.x / 4 + w->mini.plot.x, 
						plot_player.y / 4 + w->mini.plot.y, 0xbbccff);
			y++;
		}
		x++;
	}
	return (0);
}
