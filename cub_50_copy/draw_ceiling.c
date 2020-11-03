#include "cub_3d.h"

void		draw_ceiling(int i, t_ray *r, t_win *w)
{
	int		j;

	j = w->R_height / 2;
	while (j >= 0)
	{
		my_mlx_pixel_put(&w->img, i, j, 0xff0000);
		j--;
	}
}