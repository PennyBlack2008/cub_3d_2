/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:22:35 by jikang            #+#    #+#             */
/*   Updated: 2020/11/11 20:22:46 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 오른쪽 화살표 누르면 오른쪽으로 돈다.
*/

int					rotate_right(t_win *w)
{
	int				x;
	int				y;
	t_plot			plot;
	double			new_angle;

	new_angle = w->player.ang - 30 * M_PI / 180;
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(new_angle) - y * sin(new_angle) + w->player.plot.x;
			plot.y = x * sin(new_angle) + y * cos(new_angle) + w->player.plot.y;
			if (plot.x >= 0 && plot.y >= 0)
			{
				if (is_wall(plot.x, plot.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.ang += 30 * M_PI / 180;
	return (NOT_WALL);
}

/*
** 왼쪽 화살표 누르면 왼쪽으로 돈다.
*/

int					rotate_left(t_win *w)
{
	int				x;
	int				y;
	t_plot			plot;
	double			new_angle;

	new_angle = w->player.ang - 30 * M_PI / 180;
	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(new_angle) - y * sin(new_angle) + w->player.plot.x;
			plot.y = x * sin(new_angle) + y * cos(new_angle) + w->player.plot.y;
			if (plot.x >= 0 && plot.y >= 0)
			{
				if (is_wall(plot.x, plot.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	w->player.ang -= 30 * M_PI / 180;
	return (NOT_WALL);
}