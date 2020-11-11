#include "cub3d.h"

void		draw_floor(int i, t_ray *r, t_win *w)
{
	int		j;
	int		color;

	color = color_rgb(w->map.info.FL_RGB.trgb.r, w->map.info.FL_RGB.trgb.g, 
			w->map.info.FL_RGB.trgb.b);
	j = w->R_height / 2;
	while (j < w->R_height)
	{
		my_mlx_pixel_put(&w->img, i, j, color);
		j++;
	}
}
