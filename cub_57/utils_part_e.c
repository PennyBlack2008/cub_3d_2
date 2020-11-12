/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_part_e.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jikang <jikang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:53:44 by jikang            #+#    #+#             */
/*   Updated: 2020/11/12 14:20:47 by jikang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double				ft_ceil(double x)
{
	if ((x > 0 && ((double)((int)x)) + 1 - x > 1) || x == -0)
		return (x);
	return (x <= 0 ? ((double)((int)x)) : ((double)((int)x)) + 1);
}

double				ft_floor(double x)
{
	if (ft_ceil(x) == x)
		return (x);
	return (x >= 0 ? ((double)((int)x)) : ((double)((int)x)) + 1);
}
