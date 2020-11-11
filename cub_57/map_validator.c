/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 21:25:25 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 22:20:22 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_spawning_orientation(t_win *win, int x, int y, int *cnt)
{
	if (win->map.map[y][x] == 'N' || win->map.map[y][x] == 'S' ||
		win->map.map[y][x] == 'E' || win->map.map[y][x] == 'W')
	{
		win->player.plot.x = x * win->wall.length + 0.5 * win->wall.length;
		win->player.plot.y = y * win->wall.length + 0.5 * win->wall.length;
		win->player.facing = win->map.map[y][x];
		win->map.map[y][x] = '0';
		(*cnt)++;
	}
	else
		error_handler("Invalid char is exist in map!", 0);
}

static void	check_left_right(t_win *win)
{
	int y;

	y = 0;
	while (y < win->map.map_height)
	{
		if (win->map.map[y][0] == '1' || win->map.map[y][0] == ' ')
			y++;
		else
			error_handler("Invalid map!", 0);
	}
	y = 0;
	while (y < win->map.map_height)
	{
		if (win->map.map[y][win->map.map_width - 1] == '1' ||
			win->map.map[y][win->map.map_width - 1] == ' ')
			y++;
		else
			error_handler("Invalid map!", 0);
	}
}

static void	check_top_bottom(t_win *win)
{
	int x;

	x = 0;
	while (x < win->map.map_width)
	{
		if (win->map.map[0][x] == '1' || win->map.map[0][x] == ' ')
			x++;
		else
			error_handler("Invalid map!", 0);
	}
	x = 0;
	while (x < win->map.map_width)
	{
		if (win->map.map[win->map.map_height - 1][x] == '1' ||
			win->map.map[win->map.map_height - 1][x] == ' ')
			x++;
		else
			error_handler("Invalid map!", 0);
	}
}

static void	check_all_directions(t_win *win, int x, int y)
{
	const int	directx[] = {0, 1, 1, 1, 0, -1, -1, -1};
	const int	directy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int			i;
	int			nextx;
	int			nexty;

	i = 0;
	while (i < 8)
	{
		nextx = directx[i] + x;
		nexty = directy[i] + y;
		if ((nextx < 0 || nextx >= win->map.map_width) ||
			(nexty < 0 || nexty >= win->map.map_height))
		{
			i++;
			continue ;
		}
		if (win->map.map[y][x] == ' ' &&
			(win->map.map[nexty][nextx] == '0' ||
			win->map.map[nexty][nextx] == '2'))
			error_handler("Invalid map!", 0);
		i++;
	}
}

void		map_validtator(t_win *win)
{
	int cnt;
	int x;
	int y;

	check_top_bottom(win);
	check_left_right(win);
	cnt = 0;
	y = 1;
	win->num_sprite = 0;
	while (y < win->map.map_height)
	{
		x = 0;
		while (x < win->map.map_width)
		{
			if (ft_isalpha(win->map.map[y][x]))
				check_spawning_orientation(win, x, y, &cnt);
			check_all_directions(win, x, y);
			if (win->map.map[y][x] == '2')
				win->num_sprite++;
			x++;
		}
		y++;
	}
	if (cnt != 1)
		error_handler("Invalid map!", 0);
}
