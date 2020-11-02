#include "cub_3d.h"

int					get_color_spr(double x, double y, double scale_w, double scale_h, t_win *w, int k)
{
	int				color;
	double			px, py;

	px = floor(x / scale_w);
	py = floor(y / scale_h);
	color = w->map.curr_tex[k][(int)(w->tex[k].height * py + px)];
	return (color);
}

void			draw_a_sprite(int i, t_ray *r, t_win *w)
{
	double		dist_to_spr;
	double		pjtd_height;
	double		pjtd_width;
	double		orgn_pjtd_height;
	double		orgn_pjtd_width;
	double		scale_h;
	double		scale_w;
	int			color;

	dist_to_spr = hypot(r[i].spr_hit.x - w->player.x, r[i].spr_hit.y - w->player.y) * fabs(cos(r[i].ang - w->player.ang));
	pjtd_height = w->wall.height * w->player.projected_plane / dist_to_spr;
	// printf("pjtd_height: %f\n", pjtd_height);
	orgn_pjtd_height = pjtd_height;
	// orgn_pjtd_width = pjtd_height * w->aspect_ratio; // 가로 세로 비율을 통해
	pjtd_width = 300 * w->player.projected_plane / dist_to_spr;
	orgn_pjtd_width = pjtd_width;
	// printf("orgn_pjtd_width: %f\n", orgn_pjtd_width);
	scale_h = orgn_pjtd_height / 64.0; // <--- segfault 날 수도.. 스케일은 해상도를 넘어가는 벽 높이를 해상도에 맞게 조정하기 전에 랜더링을 해야하기 때문에 이 상태에서 스케일 값을 저장.
	scale_w = orgn_pjtd_width / 64.0;
	if (pjtd_height > w->R_height)
		pjtd_height = w->R_height;
	if (pjtd_width > w->R_width)
		pjtd_width = w->R_width;

	int j;		j = 0;		int k;		k = (pjtd_height / 2) - 1;

	// 중간인 500 은 위쪽 while 에서 처리
	int l;		l = -1 * pjtd_width / 2;
	// printf("%d\n", l);
	while (l < pjtd_width / 2)
	{
		j = 0;
		while (j < pjtd_height / 2 && i + l > 0) // 아래 쪽
		{
			color = get_color_spr(pjtd_width / 2 + l, orgn_pjtd_height / 2 + j, scale_w, scale_h, w, 4);
			// my_mlx_pixel_put(&w->img, i + l, w->player.height + j, 0x47E9EE);
			if (color != 0)
				my_mlx_pixel_put(&w->img, i + l, w->player.height + j, color);
			j++;
		}
		k = (pjtd_height / 2) - 1;
		while (k > 0 && i + l > 0) // 위 쪽
		{
			color = get_color_spr(pjtd_width / 2 + l, orgn_pjtd_height / 2 - k, scale_w, scale_h, w, 4);
			// my_mlx_pixel_put(&w->img, i + l, w->player.height - k, 0x47E9EE);
			if (color != 0)
				my_mlx_pixel_put(&w->img, i + l, w->player.height - k, color);
			k--;
		}
		if (i + l > w->R_width)
			break ;
		// printf("i + l: %d\n", i + l);
		l++;
	}
}