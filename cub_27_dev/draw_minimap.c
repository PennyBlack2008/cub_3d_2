#include "cub_21.h"

void				draw_minimap(t_ray *r, t_win *w)
{
	int	i;
	t_plot player;
	t_plot ray;
	t_plot spr;
	// 미니맵 그리기
	draw_map(w);
	draw_player(w);
	set_plot(&player, w->player.plot.x / 4 + w->mini.plot.x, w->player.plot.y / 4 + w->mini.plot.y);
	i = 0;
	while (i < w->R_width)
	{
		set_plot(&ray, (r[i].hit.x / 4) + w->mini.plot.x, (r[i].hit.y / 4) + w->mini.plot.y);
		set_plot(&spr, (r[i].sprite.x / 4) + w->mini.plot.x, (r[i].sprite.y / 4) + w->mini.plot.y);
		draw_line(player, ray, 0xFF0000, w);
		if (r[i].sprite.x != 0 && r[i].sprite.y != 0)
			draw_line(player, spr, 0x0000ff, w);
		i++;
	}
	draw_map_sprite(w);
	// mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
}