#include "cub3d.h"

int					get_color_spr(double x, double y, double scale_w, double scale_h, t_win *w, int k)
{
	int				color;
	double			px;
	double			py;

	px = floor(x / scale_w);
	py = floor(y / scale_h);
	color = w->map.curr_tex[k][(int)(w->tex[k].width * py + px)];
	return (color);
}

static void			draw_part_down(int i, int l, double o_pjtd_height, 
		double pjtd_height, double o_pjtd_width, double scale_w, double scale_h,
	   	t_win *w)
{
	int				color;
	int				j;

	j = 0;
	while (j < pjtd_height / 2 && i + l > 0)
	{
		color = get_color_spr(o_pjtd_width / 2 + l, o_pjtd_height / 2 + j, 
				scale_w, scale_h, w, 4);
		if (color != 0 && i + l < w->R_width)
			my_mlx_pixel_put(&w->img, i + l, w->player.height + j, color);
		j++;
	}
}

static void			draw_part_up(int i, int l, double o_pjtd_height, 
		double pjtd_height, double o_pjtd_width, double scale_w, double scale_h,
		t_win *w)
{
	int				color;
	int				k;

	k = pjtd_height / 2 - 1;
	while (k > 0)
	{
		color = get_color_spr(o_pjtd_width / 2 + l, o_pjtd_height / 2 - k, 
				scale_w, scale_h, w, 4);
		if (color != 0)
			my_mlx_pixel_put(&w->img, i + l, w->player.height - k, color);
		k--;
	}
}

void				draw_sprite_pixels(int i, double o_pjtd_width, 
		double pjtd_width, double o_pjtd_height, double pjtd_height, 
		double scale_w, double scale_h, t_ray *r, t_win *w)
{
	int				l;
 
	l = -1 * pjtd_width / 2;
	while (l < pjtd_width / 2)
	{	
		if (i + l > w->R_width)
			break ;
		if (i + l >= 0)
		{
			draw_part_down(i, l, o_pjtd_height, pjtd_height, o_pjtd_width, scale_w, scale_h, w);
			draw_part_up(i, l, o_pjtd_height, pjtd_height, o_pjtd_width, scale_w, scale_h, w);	
		}
		l++;
	}
}

void				draw_a_sprite(int i, t_ray *r, t_win *w)
{
	double			dist_to_spr;
	double			pjtd_height;
	double			o_pjtd_height;
	double			pjtd_width;
	double			o_pjtd_width;
	double			scale_h;
	double			scale_w;
	int				color;

	dist_to_spr = hypot(r[i].spr_hit.x - w->player.plot.x, r[i].spr_hit.y 
			- w->player.plot.y) * fabs(cos(r[i].ang - w->player.ang));
	if (dist_to_spr < 30)
		dist_to_spr = 30;
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_spr;
	o_pjtd_height = pjtd_height;
	pjtd_width = 300 * w->player.projected_plane / dist_to_spr;
	o_pjtd_width = pjtd_width;
	scale_h = o_pjtd_height / 64.0;
	scale_w = o_pjtd_width / 64.0;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	if (pjtd_width > w->R_width)
		pjtd_width = w->R_width;
	draw_sprite_pixels(i, o_pjtd_width, pjtd_width, o_pjtd_height, 
			pjtd_height, scale_w, scale_h, r, w);
}
