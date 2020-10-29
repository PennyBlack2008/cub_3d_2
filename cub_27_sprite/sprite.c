#include "cub_21.h"



// draw_a_ray 이후에 draw_map_sprite 가 작동해야한다.
// 여기에 ray를 적용해야 ray에 r->spr.x, r->spr.y 를 받을 수 있다.
// 현재는 render_next_frame(t_win *w) 안에 넣어 반복실행 중입니다.
void	draw_map_sprite(t_win *w)
{
	int i, j;
	t_plot sprite;

	i = 0;
	// 가로쪽으로 증가하면서 찍으려면 j < COLS 의 while 문이 먼저 나와야 한다.
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (w->map.map[i][j] == '2')
			{
				// 여기서 sprite.x, sprite.y 를 저장하자
				sprite.x = j * w->wall.length + w->wall.length / 2;
				sprite.y = i * w->wall.length + w->wall.length / 2;
				draw_a_sprite(sprite, w);
			}
			j++;
		}
		i++;
	}
}

// minimap 에 sprite를 그리는 초록색 선들
void				draw_a_sprite(t_plot sprite, t_win *w)
{
	t_plot			sprite_plot;

	w->player.ang = normalize_angle(w->player.ang);
	int	k;		k = 0;
	while (k < 50)
	{
		sprite_plot.x = sprite.x - k * sin(w->player.ang);
		sprite_plot.y = sprite.y + k * cos(w->player.ang);
		my_mlx_pixel_put(&w->img, sprite_plot.x, sprite_plot.y, 0x00ff00);
		k++;
	}
	k = 0;
	while (k >= -50)
	{
		sprite_plot.x = sprite.x - k * sin(w->player.ang);
		sprite_plot.y = sprite.y + k * cos(w->player.ang);
		my_mlx_pixel_put(&w->img, sprite_plot.x, sprite_plot.y, 0x00ff00);
		k--;
	}
	mlx_put_image_to_window(w->mlx, w->win, w->img.ptr, 0, 0);
}

/*
** 일단 sprite 중점에 광선이 닿았는 지 확인하고 중점을 중심으로 sprite를 그린다.
*/
int					is_sprite(t_plot plot, t_ray *r, t_win *w)
{
	t_plot			sprite_plot;

	r->sprite.x = 0;
	r->sprite.y = 0;
	r->spr_center.x = (int)(plot.x / w->wall.length) * w->wall.length + w->wall.length / 2;
	r->spr_center.y = (int)(plot.y / w->wall.length) * w->wall.length + w->wall.length / 2;
	// printf("x: %f, y: %f\n", r->spr_center.x, r->spr_center.y);
	// printf("x: %f, y: %f\n", plot.x, plot.y);
	// 0.5 가 제일 적당하다.
	if (fabs(r->spr_center.x - plot.x) < 0.5 && fabs(r->spr_center.y - plot.y) < 0.5)
	{
		r->sprite.x = plot.x;
		r->sprite.y = plot.y;
		// printf("x: %f, y: %f\n", r->sprite.x, r->sprite.y);
		return (1);
	}
	return (0);
}
