/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:53:38 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/03 11:18:26 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_error(int i, t_data *data)
{
	ft_putstr_fd("ERROR", 2);
	(void)data;
	exit(i);
}

void	ft_hook(void *param)
{
	int		i;
	t_data	*f;

	i = 0;
	f = param;
	key_hook(f);
	while (i < 1080)
	{
		ft_rayete (f, i);
		ft_paint_walls(f, ((WALL_H * 1) / ((f->ray->length)
					* (cos(f->ray->angle - f->player->angle)) * 1)), i);
		i++;
	}
}

void	ft_openwindow(t_data *f)
{
	mlx_loop_hook(f->mlx, &ft_hook, f);
	mlx_loop(f->mlx);
	mlx_delete_image(f->mlx, f->img);
	mlx_terminate(f->mlx);
}

static void	init_struct(t_data *data)
{
	data->fd = 0;
	data->line = NULL;
	data->texture_count = 0;
	data->char_pos = 0;
	data->height_map = 0;
	data->width_map = 0;
	data->player = malloc(sizeof(t_player));
	data->player->pos = malloc(sizeof(t_coordinate));
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->mlx = mlx_init(WIDTH, HEIGHT, "CUBESITO", false);
	if (!data->mlx)
		ft_error(MLX_ERROR, data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player->angle = 0;
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(IMG_ERROR, data);
	data->ray = malloc(sizeof(t_ray));
	data->no = malloc(sizeof(mlx_texture_t));
	data->so = malloc(sizeof(mlx_texture_t));
	data->ea = malloc(sizeof(mlx_texture_t));
	data->we = malloc(sizeof(mlx_texture_t));
	data->ceiling = malloc(sizeof(uint32_t) * 3);
	data->floor = malloc(sizeof(uint32_t) * 3);
}

static int	check_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u'
		|| file[i - 3] != 'c' || file[i - 4] != '.')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Error: Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]) == 1)
		return (printf("Error: Invalid file extension\n"), 1);
	init_struct(&data);
	if (parser(&data, argv[1]) == 1)
	{
		return (1);
	}

	ft_draw_minimap(&data);
	ft_openwindow(&data);
	return (0);
}