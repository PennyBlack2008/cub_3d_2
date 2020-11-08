#include "cub3d.h"
#define ROWS 14
#define COLS 33

void				map_init(t_win *w)
{
	int i;
	// 여기서 1 은 흰 색, 0 은 검정색이다.
	w->map.map = (char **)malloc(sizeof(char *) * ROWS);
	i = 0;
	// while (i < ROWS)
	// {
	// 	w->map.map[i] = (char *)malloc(sizeof(char) * COLS);
	// 	i++;
	// }
	// w->map.map[0] = " 111 ";
	// w->map.map[1] = "10001";
	// w->map.map[2] = "10001";
	// w->map.map[3] = "10101";
	// w->map.map[4] = "11111";

	// w->map.map[0] = "1111111111";
	// w->map.map[1] = "1000000011";
	// w->map.map[2] = "1000000011";
	// w->map.map[3] = "1000000011";
	// w->map.map[4] = "1000000011";
	// w->map.map[5] = "1000000011";
	// w->map.map[6] = "1000000011";
	// w->map.map[7] = "1000000001";
	// w->map.map[8] = "1000000001";
	// w->map.map[9] = "1100000111";
	// w->map.map[10] = "1111111111";
	// w->map.map[0] = ft_strdup("        1111111111111111111111111");
	// w->map.map[1] = ft_strdup("        1000000000110000000000001");
	// w->map.map[2] = ft_strdup("        1011000001110000002000001");
	// w->map.map[3] = ft_strdup("        1001000000000000000000001");
	// w->map.map[4] = ft_strdup("111111111011000001110000000000001");
	// w->map.map[5] = ft_strdup("100000000011000001110111111111111");
	// w->map.map[6] = ft_strdup("11110111111111011100000010001    ");
	// w->map.map[7] = ft_strdup("11110111111111011101010010001    ");
	// w->map.map[8] = ft_strdup("11000000110101011100000010001    ");
	// w->map.map[9] = ft_strdup("10002000000000001100000010001    ");
	// w->map.map[10] = ft_strdup("10000000000000001101010010001    ");
	// w->map.map[11] = ft_strdup("11000001110101011111011110N0111  ");
	// w->map.map[12] = ft_strdup("11110111 1110101 101111010001    ");
	// w->map.map[13] = ft_strdup("10000000000000001101010010001    ");

	w->map.map[0] = ft_strdup("        1111111111111111111111111");
	w->map.map[1] = ft_strdup("        1000000000110000000000001");
	w->map.map[2] = ft_strdup("        1011000001110000002000001");
	w->map.map[3] = ft_strdup("        1001000000000000000000001");
	w->map.map[4] = ft_strdup("111111111111111111111111111111111");
	w->map.map[5] = ft_strdup("100000000011000001110111111111111");
	w->map.map[6] = ft_strdup("11110111111111011100000010001    ");
	w->map.map[7] = ft_strdup("11110111111111011101010010001    ");
	w->map.map[8] = ft_strdup("11000000110101011100000010001    ");
	w->map.map[9] = ft_strdup("10002000000000001100000010001    ");
	w->map.map[10] = ft_strdup("10000000000000001101010010001    ");
	w->map.map[11] = ft_strdup("11000001110101011111011110N0111  ");
	w->map.map[12] = ft_strdup("11110111 1110101 101111010001    ");
	w->map.map[13] = ft_strdup("11111111 1111111 111111111111    ");

	w->player.x = 27 * w->wall.length + w->wall.length / 2; 
	w->player.y = 12 * w->wall.length + w->wall.length / 2;
	w->player.ang = M_PI_2 * 3;
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
