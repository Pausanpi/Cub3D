/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:53:38 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/04 16:55:53 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

static void	ft_hook(void *param)
{
	int		i;
	t_data	*f;

	i = 0;
	f = param;
	key_hook(f);
	while (i < 1080)
	{
		ft_rayete(f, i);
		ft_paint_walls(f, ((WALL_H * 1) / ((f->ray->length) * (cos(f->ray->angle - f->player->angle)) * 1)), i);
		i++;
	}
}

static void	ft_openwindow(t_data *f)
{
	mlx_loop_hook(f->mlx, &ft_hook, f);
	mlx_loop(f->mlx);

}

static int	check_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (print_error("Invalid number of arguments"), 1);
	if (check_extension(argv[1]) == 1)
		return (print_error("Invalid file extension"), 1);
	init_struct(&data);
	if (parser(&data, argv[1]) == 1)
		return (1);
	init_mlx(&data);
	ft_init_pos(&data);
	ft_openwindow(&data);
	ft_exit(&data);
	return (0);
}
