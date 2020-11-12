/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:28:35 by jikang            #+#    #+#             */
/*   Updated: 2020/11/12 13:53:52 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				forward(t_win *w)
{
	w->player.plot.x += 30 * cos(w->player.ang * -1);
	w->player.plot.y -= 30 * sin(w->player.ang * -1);
}

void				backward(t_win *w)
{
	w->player.plot.x -= 30 * cos(w->player.ang * -1);
	w->player.plot.y += 30 * sin(w->player.ang * -1);
}

void				leftward(t_win *w)
{
	w->player.plot.x -= 30 * cos(M_PI_2 - (w->player.ang * -1));
	w->player.plot.y -= 30 * sin(M_PI_2 - (w->player.ang * -1));
}

void				rightward(t_win *w)
{
	w->player.plot.x += 30 * cos(M_PI_2 - (w->player.ang * -1));
	w->player.plot.y += 30 * sin(M_PI_2 - (w->player.ang * -1));
}
