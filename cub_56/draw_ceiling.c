#include "cub3d.h"

void		draw_ceiling(int i, t_ray *r, t_win *w)
{
	int		j;
	int		color;

	color = color_rgb(w->map.info.CL_R, w->map.info.CL_G, w->map.info.CL_B);
	j = w->R_height / 2;
	while (j >= 0)
	{
		my_mlx_pixel_put(&w->img, i, j, color);
		j--;
	}
}