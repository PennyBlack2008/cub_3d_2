#include "cub_21.h"

double				normalize_angle(double ang)
{
	while (ang >= 2 * M_PI)
		ang -= 2 * M_PI;
	while (ang < 0)
		ang += 2 * M_PI;
	return (ang);
}

void				set_plot(t_plot *plot, double x, double y)
{
	plot->x = x;
	plot->y = y;
}