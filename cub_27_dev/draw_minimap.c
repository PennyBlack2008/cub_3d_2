#include "cub_21.h"

void				draw_minimap(t_ray *r, t_win *w)
{
	int	i;
	t_plot player;
	t_plot ray;
	// 미니맵 그리기
	draw_map(w);
	draw_player(w);
	set_plot_int(&player, (w->player.plot.x / 4) + w->mini.plot.x, (w->player.plot.y / 4) + w->mini.plot.y);
	i = 0;
	while (i < w->R_width)
	{
		set_plot_int(&ray, (r[i].hit.x / 4) + w->mini.plot.x, (r[i].hit.y / 4) + w->mini.plot.y);
		draw_line(player, ray, 0xFF0000, w);
		i++;
	}
}