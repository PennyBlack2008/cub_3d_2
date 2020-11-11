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
	double 			new_angle;

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
				+ w->player.plot.x + 30 * cos(w->player.ang);
			plot.y = x * sin(w->player.ang) + y * cos(w->player.ang)
				+ w->player.plot.y + 30 * sin(w->player.ang);
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
				+ w->player.plot.x - 30 * cos(w->player.ang);
			plot.y = x * sin(w->player.ang) * -1 + y * cos(w->player.ang)
				+ w->player.plot.y - 30 * sin(w->player.ang);
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
				+ w->player.plot.x - 30 * cos(M_PI_2 - (w->player.ang * -1));
			plot.y = x * sin(w->player.ang) + y * cos(w->player.ang)
				+ w->player.plot.y - 30 * sin(M_PI_2 - (w->player.ang * -1));
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
	t_plot	plot_player;

	x = w->player.width / 2 * -1;
	while (x < w->player.width / 2)
	{
		y = w->player.width / 2 * -1;
		while (y < w->player.width / 2)
		{
			plot_player.x = x * cos(w->player.ang) - y * sin(w->player.ang) + 
			w->player.plot.x + 30 * cos(M_PI_2 - (w->player.ang * -1));
			plot_player.y = x * sin(w->player.ang) + y * cos(w->player.ang) + 
			w->player.plot.y + 30 * sin(M_PI_2 - (w->player.ang * -1));
			if (plot_player.x >= 0 && plot_player.y >= 0)
			{
				if (is_wall(plot_player.x, plot_player.y, w) == WALL)
					return (WALL);
			}
			y++;
		}
		x++;
	}
	rightward(w);
	return (NOT_WALL);
}
