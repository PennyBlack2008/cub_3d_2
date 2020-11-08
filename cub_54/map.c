#include "cub3d.h"
// m->map_width
// m->map_height;
void				map_init(t_win *w)
{
	int i;
	int	j;
	// 여기서 1 은 흰 색, 0 은 검정색이다.
	init_game_map(&(w->map));
	// 6. 벽의 크기와 높이 설정
	w->wall.length = 150;
	w->wall.height = 600;
	printf("Sprite texture dir: %s\n", w->map.info.sprite_texture);
	printf("1 %p\n", &(w->map));
	printf("w->R_width: %d\n", w->map.info.R_width);
	printf("w->R_width: %d\n", w->map.info.R_height);
	i = 0;
	while (i < w->map.map_width)
	{
		j = 0;
		while (j < w->map.map_height)
		{
			if (w->map.map[j][i] == 'N')
			{
				w->player.plot.x = w->wall.length * i + w->wall.length * 0.5;
				w->player.plot.y = w->wall.length * j + w->wall.length * 0.5;
				w->player.ang = M_PI_2 * 3;
			}
			else if (w->map.map[j][i] == 'S')
			{
				w->player.plot.x = w->wall.length * i + w->wall.length * 0.5;
				w->player.plot.y = w->wall.length * j + w->wall.length * 0.5;
				w->player.ang = M_PI_2 * 1;
			}
			else if (w->map.map[j][i] == 'E')
			{
				w->player.plot.x = w->wall.length * i + w->wall.length * 0.5;
				w->player.plot.y = w->wall.length * j + w->wall.length * 0.5;
				w->player.ang = M_PI_2 * 0;
			}
			else if (w->map.map[j][i] == 'W')
			{
				w->player.plot.x = w->wall.length * i + w->wall.length * 0.5;
				w->player.plot.y = w->wall.length * j + w->wall.length * 0.5;
				w->player.ang = M_PI_2 * 2;
			}
		}
		i++;
	}	
	w->player.plot.x = 27 * w->wall.length + w->wall.length / 2; 
	w->player.plot.y = 12 * w->wall.length + w->wall.length / 2;
	w->player.ang = M_PI_2 * 3;
	write(1, "hi\n", 4);
	
}

// void				draw_rectangle(t_win *w, int x, int y, int color)
// {
// 	int i, j;

// 	x *= w->wall.length;
// 	y *= w->wall.length;
// 	i = 0;
// 	while (i < w->wall.length)
// 	{
// 		j = 0;
// 		while (j < w->wall.length)
// 		{
// 			my_mlx_pixel_put(&w->img, (y + i) / 4 + w->mini.plot.x, (x + j) / 4 + w->mini.plot.y, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void				draw_map(t_win *w)
// {
// 	int i, j;

// 	i = 0;
// 	// 가로쪽으로 증가하면서 찍으려면 j < COLS 의 while 문이 먼저 나와야 한다.
// 	while (i < ROWS)
// 	{
// 		j = 0;
// 		while (j < COLS)
// 		{
// 			if (w->map.map[i][j] == '1')
// 				draw_rectangle(w, i, j, 0xFFFFFF);
// 			else
// 				draw_rectangle(w, i, j, 0x000000);
// 			j++;
// 		}
// 		i++;
// 	}
// }


// void	draw_spr_rectangle(t_win *w, int x, int y, int color)
// {
// 	int i, j;

// 	x *= w->wall.length;
// 	y *= w->wall.length;
// 	i = 0;
// 	while (i < w->wall.length / 3)
// 	{
// 		j = 0;
// 		while (j < w->wall.length / 3)
// 		{
// 			my_mlx_pixel_put(&w->img, (y + i + w->wall.length / 3) / 4 + w->mini.plot.x, (x + j + w->wall.length / 3) / 4 + w->mini.plot.y, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_sprite_in_minimap(t_win *w)
// {
// 	int i, j;

// 	i = 0;
// 	while (i < ROWS)
// 	{
// 		j = 0;
// 		while (j < COLS)
// 		{
// 			if (w->map.map[i][j] == '2')
// 				draw_spr_rectangle(w, i, j, 0x58D68D);
// 			j++;
// 		}
// 		i++;
// 	}
// }

/*
** int						is_wall(int x, int y, t_win *w)
** 확인하고자 하는 픽셀의 좌표를 넣으면 그 픽셀이 벽인지 확인 해주는 함수, 1이면 벽, 0이면 벽이 아니다.
** 픽셀 좌표 x, y 에 각각 w->wall.length, w->wall.length 를 나누어 이것이 char **map에 어떤 인덱스에
** 속하는 지 알아보고 map[x * w->wall.length][y * w->wall.length]가 0이면 벽이아니고 1이면 벽으로 결정
*/

int					is_wall(double x, double y, t_win *w)
{
	if (w->map.map[(int)(y / w->wall.length)][(int)(x / w->wall.length)] == WALL || 
	w->map.map[(int)(y / w->wall.length)][(int)(x / w->wall.length)] == ' ')
		return (WALL);
	else if (w->map.map[(int)(y / w->wall.length)][(int)(x / w->wall.length)] == SPRITE)
	{
		if (fabs((int)(y / w->wall.length) * w->wall.length + w->wall.length * 0.5 - y) < 1 && fabs((int)(x / w->wall.length) * w->wall.length + w->wall.length * 0.5 - x) < 1)
			return (SPRITE);
	}
	return (NOT_WALL);
}
