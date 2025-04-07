/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:29 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:23:26 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_usage(void)
{
	ft_putstr_fd("Kullanım: ./fractol <tip> [julia_real] [julia_imag]\n", 1);
	ft_putstr_fd("Tipler:\n", 1);
	ft_putstr_fd("  mandelbrot\n", 1);
	ft_putstr_fd("  julia\n", 1);
	ft_putstr_fd("\nJulia seti için gerçek ve sanal kısımları belirtebilirsiniz:\n", 1);
	ft_putstr_fd("Örnek: ./fractol julia -0.4 0.6\n", 1);
}

double	ft_atof(char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0.0;
	decimal = 0.0;
	sign = 1;
	i = 0;  
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}   
	while (str[i] && str[i] != '.')
		result = result * 10.0 + (str[i++] - '0');  
	if (str[i] == '.')
	{
		i++;
		double factor = 0.1;
		while (str[i])
		{
			decimal += (str[i++] - '0') * factor;
			factor *= 0.1;
		}
	}
	return (sign * (result + decimal));
}

int	parse_args(int argc, char **argv, t_fractol *f)
{
	if (argc < 2)
		return (1);
	if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		f->type = MANDELBROT;
	else if (ft_strncmp(argv[1], "julia", 5) == 0)
	{
		f->type = JULIA;	
		if (argc >= 4)
		{
			f->julia_c.real = ft_atof(argv[2]);
			f->julia_c.imag = ft_atof(argv[3]);
		}
		else
		{
			f->julia_c.real = -0.4;
			f->julia_c.imag = 0.6;
		}
	}
	else
		return (1);
	return (0);
}


void	put_pixel(t_fractol *f, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = f->img.addr + (y * f->img.line_length + x * (f->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

int	create_color(int iterations, t_fractol *f)
{
	double	t;
	int		r, g, b;	
	if (iterations == f->max_iter)
		return (0x000000);

	t = (double)iterations / f->max_iter;

	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

	return (r << 16 | g << 8 | b);
}

double	map(double value, double from[2], double to[2])
{
	return (to[0] + (value - from[0]) * (to[1] - to[0]) / (from[1] - from[0]));
}
