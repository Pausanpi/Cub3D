/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:53:38 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/29 12:42:04 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_error(int i, t_data *data)
{
	ft_putstr_fd("ERROR", 2);
	(void)data;
	exit(i);
}

void	ft_paint_walls(t_data *f, float wall, int col) //abr'ia que a;adirle la colision
{
	int	j;
	int	top;
	int	bot;

	top = HEIGHT / 2 - wall / 2;
	if (top < 0)
		top = 0;
	bot = top + wall;
	j = 0;
//	ft_init_pixel(coll, wall, info); esto pa decidir que pixeles, la textura
	while (j < HEIGHT)
	{
		if (j < top)
			mlx_put_pixel(f->img, col, j, (255 << 24 | 255 << 16 | 255 << 8 | 150));
		else if (j > bot)
			mlx_put_pixel(f->img, col, j, 99999999);
		else if (f->ray->x_sign == 1 && f->ray->last_cross == 0)
			mlx_put_pixel(f->img, col, j, (255 << 24 | 0 << 16 | 0 << 8 | 100));
		else if (f->ray->x_sign == -1 && f->ray->last_cross == 0)
			mlx_put_pixel(f->img, col, j, 22222222);
		else if (f->ray->y_sign == 1 && f->ray->last_cross == 1)
			mlx_put_pixel(f->img, col, j, 33333333);
		else if (f->ray->y_sign == -1 && f->ray->last_cross == 1)
			mlx_put_pixel(f->img, col, j, 44444444);
		j++;

	}
//	ft_draw_walls(info, coll, col, top);
}

void	ft_hook(void *param)
{
	t_data	*f;
	int		i;

	f = param;
	if (mlx_is_key_down(f->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(f->mlx);
	if (mlx_is_key_down(f->mlx, MLX_KEY_W))
		f->player->pos->x += 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_S))
		f->player->pos->x -= 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_D))
		f->player->pos->y += 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_A))
		f->player->pos->y -= 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_E))
		f->player->angle += 0.05;
	if (mlx_is_key_down(f->mlx, MLX_KEY_Q))
		f->player->angle -= 0.05;
	i = 0;
	while (i < 1080)
	{
		ft_rayete (f, i);
		ft_paint_walls(f, (WALL_H - (f->ray->length) * 40), i); // habia uqe añadirle datos de colision
		i += 1;
	}
}

void	ft_openwindow(t_data *f)
{
	mlx_loop_hook(f->mlx, &ft_hook, f);
	mlx_loop(f->mlx);
	mlx_delete_image(f->mlx, f->img);
	mlx_terminate(f->mlx);
}

static void init_struct(t_data *data)
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
	data->mlx = mlx_init(WIDTH, HEIGHT, "VENTANA", false);
	if (!data->mlx)
		ft_error(MLX_ERROR, data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player->angle = 0;
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(IMG_ERROR, data);

	data->ray = malloc(sizeof(t_ray));
	
}

static int check_extension(char *file)
{
    int i;

    i = 0;
    while (file[i])
        i++;
    if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
        return (1);
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
        return (printf("Error: Invalid number of arguments\n"), 1);
    if (check_extension(argv[1]) == 1)
        return (printf("Error: Invalid file extension\n"), 1);
    init_struct(&data);
    if (parser(&data, argv[1]) == 1)
	{
        return (1);
	}

	int i = 0;
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}

	ft_openwindow(&data);
	return (0);
}