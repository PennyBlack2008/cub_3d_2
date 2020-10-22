#include "utils.h"

double				normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

void				set_plot_int(t_plot *plot, int x, int y)
{
	plot->x = x;
	plot->y = y;
}