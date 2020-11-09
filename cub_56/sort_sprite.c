#include "cub3d.h"

void			sort_sprite(t_sprite *spr, t_win *w)
{
	int			k;
	int			l;
	t_sprite	temp;

	k = 0;
	while (k < w->num_sprite)
	{
		l = 0;
		while (l < w->num_sprite - (k + 1))
		{
			if (spr[l].dist < spr[l + 1].dist)
			{
				temp.i = spr[l + 1].i;
				temp.dist = spr[l + 1].dist;
				spr[l + 1].i = spr[l].i;
				spr[l + 1].dist = spr[l].dist;
				spr[l].i = temp.i;
				spr[l].dist = temp.dist;
			}
			l++;
		}
		k++;
	}
}

void			draw_sprites(t_sprite *spr, t_ray *r, t_win *w)
{
	int			k;

	sort_sprite(spr, w);
	k = 0;
	while (spr[k].dist != 0)
	{
		draw_a_sprite(spr[k].i, r, w);
		k++;
	}
}
