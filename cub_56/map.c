#include "cub3d.h"

void				map_init(t_win *w)
{
	int				i;
	int				j;

	i = 0;
	while (i < w->map.map_height)
	{
		j = 0;
		while (j < w->map.map_width)
		{
			printf("%c", w->map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return ;
}

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
		if (fabs((int)(y / w->wall.length) * w->wall.length + w->wall.length * 0.5 - y) < 0.1 && fabs((int)(x / w->wall.length) * w->wall.length + w->wall.length * 0.5 - x) < 0.1)
			return (SPRITE);
	}
	return (NOT_WALL);
}
