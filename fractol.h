/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:17 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:18 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define MAX_ITERATIONS 100

typedef	enum	e_fractal_type {
	MANDELBROT,
	JULIA
} t_fractal_type;

typedef	struct	s_complex {
	double	real;
	double	imag;
} t_complex;

typedef	struct	s_color {
	int	r;
	int	g;
	int	b;
} t_color;

typedef	struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;

typedef	struct	s_fractol {
	void			*mlx;
	void			*win;
	t_img			img;
	t_fractal_type	type;
	t_complex		julia_c;
	double			zoom;
	double			move_x;
	double			move_y;
	int				max_iter;
	t_color			color;
} t_fractol;

void	init_fractol(t_fractol *f, char *title);
int		render_fractol(t_fractol *f);
void	calculate_pixel(t_fractol *f, int x, int	
int		handle_keypress(int keycode, t_fractol *f);
int		handle_mouse(int button, int x, int y, t_fractol *f);
int		close_window(t_fractol *
int		mandelbrot_iteration(t_complex c, int max_iter);
int		julia_iteration(t_complex z, t_complex c, int max_ite
void	put_pixel(t_fractol *f, int x, int y, int color);
int		create_color(int iterations, t_fractol *f);
int		parse_args(int argc, char **argv, t_fractol *f);
void	print_usage(void);
double	map(double value, double from[2], double to[2]);

#endif