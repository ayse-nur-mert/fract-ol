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

int	handle_keypress(int keycode, t_fractol *f)
{
	if (keycode == 65307) // ESC
		close_window(f);
	else if (keycode == 65361) // Sol ok
		f->move_x -= 0.1 / f->zoom;
	else if (keycode == 65363) // Sağ ok
		f->move_x += 0.1 / f->zoom;
	else if (keycode == 65362) // Yukarı ok
		f->move_y -= 0.1 / f->zoom;
	else if (keycode == 65364) // Aşağı ok
		f->move_y += 0.1 / f->zoom;
	else if (keycode == 65451) // Numpad +
		f->max_iter += 10;
	else if (keycode == 65453) // Numpad -
		f->max_iter = f->max_iter > 10 ? f->max_iter - 10 : f->max_iter;

	render_fractol(f);
	return (0);
}

int handle_mouse(int button, int x, int y, t_fractol *f)
{
	double zoom_factor;
	double x_before;
	double y_before;

	if (button == 4 || button == 5) // Tekerlek yukarı/aşağı
	{
		// Zoom öncesi koordinatları hesapla
		x_before = (x - WINDOW_WIDTH / 2.0) / (0.5 * WINDOW_WIDTH * f->zoom) + f->move_x;
		y_before = (y - WINDOW_HEIGHT / 2.0) / (0.5 * WINDOW_HEIGHT * f->zoom) + f->move_y;

		// Zoom faktörünü uygula
		zoom_factor = (button == 4) ? 1.2 : 0.8;
		f->zoom *= zoom_factor;

		// Yeni koordinatları hesapla ve kaydırma değerlerini güncelle
		f->move_x = x_before - (x - WINDOW_WIDTH / 2.0) / (0.5 * WINDOW_WIDTH * f->zoom);
		f->move_y = y_before - (y - WINDOW_HEIGHT / 2.0) / (0.5 * WINDOW_HEIGHT * f->zoom);

		render_fractol(f);
	}
	return (0);
}

int close_window(t_fractol *f)
{
	cleanup(f);
	exit(0);
	return (0);
}

void cleanup(t_fractol *f)
{
    if (f->img.img)
    {
        mlx_destroy_image(f->mlx, f->img.img);
        f->img.img = NULL; // Çift serbest bırakmayı önlemek için NULL yap
    }
    if (f->win)
    {
        mlx_destroy_window(f->mlx, f->win);
        f->win = NULL; // Çift serbest bırakmayı önlemek için NULL yap
    }
        f->mlx = NULL;
}