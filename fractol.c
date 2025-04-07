/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:22 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:23 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void init_fractol(t_fractol *f, char *title)
{
    f->mlx = mlx_init();
    if (!f->mlx)
    {
        fprintf(stderr, "Error: Failed to initialize mlx.\n");
        exit(1);
    }

    f->win = mlx_new_window(f->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
    if (!f->win)
    {
        fprintf(stderr, "Error: Failed to create window.\n");
        cleanup(f);
        exit(1);
    }

    // Tüm alanları sıfırla
    f->zoom = 1.0;
    f->move_x = 0.0;
    f->move_y = 0.0;
    f->max_iter = MAX_ITERATIONS;
    f->img.img = NULL;
}

int mandelbrot_iteration(t_complex c, int max_iter)
{
	t_complex z;
	int i;
	double temp;

	z.real = 0;
	z.imag = 0;
	i = 0;
	while (i < max_iter)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		if (z.real * z.real + z.imag * z.imag > 4)
			return (i);
		i++;
	}
	return (max_iter);
}

int julia_iteration(t_complex z, t_complex c, int max_iter)
{
	int i;
	double temp;

	i = 0;
	while (i < max_iter)
	{
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.real * z.imag + c.imag;
		z.real = temp;
		if (z.real * z.real + z.imag * z.imag > 4)
			return (i);
		i++;
	}
	return (max_iter);
}

void calculate_pixel(t_fractol *f, int x, int y)
{
	t_complex c;
	double x_scaled;
	double y_scaled;
	int iterations; 
	x_scaled = (x - WINDOW_WIDTH / 2.0) / (0.5 * WINDOW_WIDTH * f->zoom) + f->move_x;
	y_scaled = (y - WINDOW_HEIGHT / 2.0) / (0.5 * WINDOW_HEIGHT * f->zoom) + f->move_y; 
	if (f->type == MANDELBROT)
	{
		c.real = x_scaled;
		c.imag = y_scaled;
		iterations = mandelbrot_iteration(c, f->max_iter);
	}
	else
	{
		c = f->julia_c;
		t_complex z = {x_scaled, y_scaled};
		iterations = julia_iteration(z, c, f->max_iter);
	}
	put_pixel(f, x, y, create_color(iterations, f));
}

int render_fractol(t_fractol *f)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			calculate_pixel(f, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
	return (0);
}