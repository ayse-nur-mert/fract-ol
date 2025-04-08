/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:20:20 by amert             #+#    #+#             */
/*   Updated: 2025/04/06 16:20:21 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_fractol	f;

	if (parse_args(argc, argv, &f) != 0)
	{
		print_usage();
		return (1);
	}
	init_fractol(&f, argv[1]);
	render_fractol(&f);
	mlx_hook(f.win, 2, 1L << 0, handle_keypress, &f);
	mlx_hook(f.win, 17, 0, close_window, &f);
	mlx_mouse_hook(f.win, handle_mouse, &f);
	mlx_loop(f.mlx);
	return (0);
}
