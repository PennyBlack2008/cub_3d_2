/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:20:14 by jikang            #+#    #+#             */
/*   Updated: 2020/11/12 16:46:02 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					move_forward(t_win *w)
{
	int				x;
	int				y;
	t_plot			plot;

	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang) - y * sin(w->player.ang)
				+ w->player.plot.x + 31 * cos(w->player.ang);
			plot.y = x * sin(w->player.ang) + y * cos(w->player.ang)
				+ w->player.plot.y + 31 * sin(w->player.ang);
			if (plot.x >= 0 && plot.y >= 0)
			{
				if (is_wall(plot.x, plot.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	forward(w);
	return (NOT_WALL);
}

int					move_back(t_win *w)
{
	int				x;
	int				y;
	t_plot			plot;

	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang) + y * sin(w->player.ang)
				+ w->player.plot.x - 31 * cos(w->player.ang);
			plot.y = x * sin(w->player.ang) * -1 + y * cos(w->player.ang)
				+ w->player.plot.y - 31 * sin(w->player.ang);
			if (plot.x >= 0 && plot.y >= 0)
			{
				if (is_wall(plot.x, plot.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	backward(w);
	return (NOT_WALL);
}

int					move_left(t_win *w)
{
	int				x;
	int				y;
	t_plot			plot;

	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang) - y * sin(w->player.ang)
				+ w->player.plot.x - 31 * cos(M_PI_2 - (w->player.ang * -1));
			plot.y = x * sin(w->player.ang) + y * cos(w->player.ang)
				+ w->player.plot.y - 31 * sin(M_PI_2 - (w->player.ang * -1));
			if (plot.x >= 0 && plot.y >= 0)
			{
				if (is_wall(plot.x, plot.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	leftward(w);
	return (NOT_WALL);
}

int					move_right(t_win *w)
{
	int				x;
	int				y;
	t_plot			plot;

	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot.x = x * cos(w->player.ang) - y * sin(w->player.ang) +
			w->player.plot.x + 31 * cos(M_PI_2 - (w->player.ang * -1));
			plot.y = x * sin(w->player.ang) + y * cos(w->player.ang) +
			w->player.plot.y + 31 * sin(M_PI_2 - (w->player.ang * -1));
			if (plot.x >= 0 && plot.y >= 0)
			{
				if (is_wall(plot.x, plot.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	rightward(w);
	return (NOT_WALL);
}
