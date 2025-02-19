/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:27:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/19 11:11:08 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void	ft_comprb(char **text_walls, int i)
{
	if (ft_strlen(text_walls[i]) <= 3)
	{
		ft_printf("Error\n");
		exit(1);
	}
}

void	print_error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

static int	check_ext_wall(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] != 'g' || path[i - 2] != 'n'
		|| path[i - 3] != 'p' || path[i - 4] != '.')
		return (1);
	return (0);
}

int	save_texture_wall(t_data *data, char **path_text_walls)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path_text_walls[i] && i < 4)
	{
		if (!path_text_walls[i] || check_ext_wall(path_text_walls[i]))
			return (print_error("Incorrect path texture"), 1);
		i++;
	}
	data->no = mlx_load_png(path_text_walls[0]);
	data->so = mlx_load_png(path_text_walls[1]);
	data->ea = mlx_load_png(path_text_walls[2]);
	data->we = mlx_load_png(path_text_walls[3]);
	return (0);
}
