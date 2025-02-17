/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:27:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/17 10:59:03 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

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
		else if ((ft_strncmp(data->line, "NO", 2)))
			data->no = mlx_load_png(path_text_walls[0]);
		else if ((ft_strncmp(data->line, "SO", 2)))
			data->so = mlx_load_png(path_text_walls[1]);
		else if ((ft_strncmp(data->line, "EA", 2)))
			data->ea = mlx_load_png(path_text_walls[2]);
		else if ((ft_strncmp(data->line, "WE", 2)))
			data->we = mlx_load_png(path_text_walls[3]);
		i++;
	}
	return (0);
}
