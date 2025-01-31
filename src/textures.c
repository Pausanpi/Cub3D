/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/31 18:02:50 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

void initialize_colors(t_data *data)
{
    int	i;

	i = 0;
	while (i < 3)
	{
		data->ceiling[i] = 0;
		data->floor[i] = 0;
		i++;
	}
}

int validate_and_assign_colors(uint32_t *color_array, char **rgb)
{
    int j;
	int color_val;

	j = 0;
    while (j < 3)
    {
        color_val = ft_atoi(rgb[j]);
        if (color_val < 0 || color_val > 255)
        {
            while (rgb[j])
            {
                free(rgb[j]);
                j++;
            }
            free(rgb);
            return (1);
        }
        color_array[j] = color_val;
        j++;
    }
    return (0);
}

void free_rgb_array(char **rgb)
{
    int j = 0;
    while (rgb[j])
    {
        free(rgb[j]);
        j++;
    }
    free(rgb);
}

int process_color_line(char *line, uint32_t *color_array)
{
    char **rgb = ft_split(line + 2, ',');
    if (!rgb)
        return (1);
    
    if (validate_and_assign_colors(color_array, rgb))
        return (1);
    
    free_rgb_array(rgb);
    return (0);
}

int color_check(t_data *data, char **text_walls)
{
    initialize_colors(data);
    int i = 3;
    while (text_walls[i])
    {
        while (text_walls[i][0] == ' ')
            text_walls[i]++;
        
        if (text_walls[i][0] == 'C' && text_walls[i][1] == ' ')
        {
            if (process_color_line(text_walls[i], data->ceiling))
                return (1);
        }
        else if (text_walls[i][0] == 'F' && text_walls[i][1] == ' ')
        {
            if (process_color_line(text_walls[i], data->floor))
                return (1);
        }
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
