#include "cub_3d.h"

void		draw_floor(int i, t_ray *r, t_win *w)
{
	int		j;

	j = w->R_height / 2;
	while (j <= w->R_height)
	{
		my_mlx_pixel_put(&w->img, i, j, 0x0000ff);
		j++;
	}
}