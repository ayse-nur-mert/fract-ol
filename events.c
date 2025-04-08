/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:25 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:26 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

int	handle_keypress(int keycode, t_fractol *f)
{
	if (keycode == 65307)
		close_window(f);
	else if (keycode == 65361)
		f->move_x -= 0.1 / f->zoom;
	else if (keycode == 65363)
		f->move_x += 0.1 / f->zoom;
	else if (keycode == 65362)
		f->move_y -= 0.1 / f->zoom;
	else if (keycode == 65364)
		f->move_y += 0.1 / f->zoom;
	else if (keycode == 113)
		f->max_iter += 10;
	else if (keycode == 101)
	{
		if (f->max_iter > 10)
			f->max_iter -= 10;
		else
			f->max_iter = 0;
	}
	render_fractol(f);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;
	double	x_before;
	double	y_before;

	if (button == 4 || button == 5)
	{
		x_before = (x - WINDOW_WIDTH / 2.0)
			/ (0.5 * WINDOW_WIDTH * f->zoom) + f->move_x;
		y_before = (y - WINDOW_HEIGHT / 2.0)
			/ (0.5 * WINDOW_HEIGHT * f->zoom) + f->move_y;
		if (button == 4)
			zoom_factor = 1.2;
		else
			zoom_factor = 0.8;
		f->zoom *= zoom_factor;
		f->move_x = x_before - (x - WINDOW_WIDTH / 2.0)
			/ (0.5 * WINDOW_WIDTH * f->zoom);
		f->move_y = y_before - (y - WINDOW_HEIGHT / 2.0)
			/ (0.5 * WINDOW_HEIGHT * f->zoom);
		render_fractol(f);
	}
	return (0);
}

int	close_window(t_fractol *f)
{
	mlx_destroy_image(f->mlx, f->img.img);
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
	return (0);
}

double	map(double value, double from[2], double to[2])
{
	return (to[0] + (value - from[0]) * (to[1] - to[0]) / (from[1] - from[0]));
}
