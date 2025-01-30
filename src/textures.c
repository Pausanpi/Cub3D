/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/30 15:30:13 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

char *ft_strncpy(char *dest, const char *src, size_t pos) {
    size_t i;
    size_t j;

	i = 0;
	j = 0;
    while (i < pos && src[i] != '\0') {
        i++;
    }
    while (src[i] != '\0') {
        dest[j] = src[i];
        i++;
        j++;
    }
    dest[j] = '\0';
    return dest;
}

int color_check(t_data *data, char **text_walls)
{
	int i;
	int j;
	char *color;
	char **rgb;

	i = 3;
	while (text_walls[i])
	{
		if (ft_strncmp(text_walls[i], "C ", 2))  // por alguna razon se guardan al reves
		{
			color = ft_strncpy(color, text_walls[i], 2);
			rgb = ft_split(color, ',');
			j = 0;
			while (rgb[j])
			{
				data->floor[j] = ft_atoi(rgb[j]);
				j++;
			}
		}
		else if (ft_strncmp(text_walls[i], "F ", 2))
		{
			color = ft_strncpy(color, text_walls[i], 2);
			rgb = ft_split(color, ',');
			j = 0;
			while (rgb[j])
			{
				data->ceiling[j] = ft_atoi(rgb[j]);
				j++;
			}
		}
		else
			return (1);
		i++;
	}
	
	return (0);
}

void load_textures(t_data *data, char *textures)
{
	char **text_walls;
	char **path_text_walls;
	int i;
	int j;

	text_walls = ft_split(textures, '\n');

	path_text_walls = malloc(sizeof(char *) * 4);
	i = 0;
	while (i <= 3)
	{
		path_text_walls[i] = malloc(sizeof(char) * 100);
		j = 3;
		while (text_walls[i][j])
		{
			path_text_walls[i][j - 3] = text_walls[i][j];
			j++;
		}
		path_text_walls[i][j - 3] = '\0';
		i++;
	}
	data->no = mlx_load_png(path_text_walls[0]);
	data->so = mlx_load_png(path_text_walls[1]);
	data->ea = mlx_load_png(path_text_walls[2]);
	data->we = mlx_load_png(path_text_walls[3]);

	color_check(data, text_walls);
}
