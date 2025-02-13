/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:06:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/04 17:08:34 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

/*
	Pone en 0 los colores del techo y el suelo
*/
void	initialize_colors(t_data *data)
{
	data->ceiling = malloc(sizeof(uint32_t) * 3);
	data->floor = malloc(sizeof(uint32_t) * 3);
	if (!data->ceiling || !data->floor)
		return ;
	ft_memset(data->ceiling, 0, sizeof(uint32_t) * 3);
	ft_memset(data->floor, 0, sizeof(uint32_t) * 3);
}

/*
	Convierte los valores en RGB en enteros
	Verifica que estén en el rango 0 - 255
	Si hay un error, libera la memoria y retorna 1
*/
int	validate_and_assign_colors(uint32_t *color_array, char **rgb)
{
	int	i;
	int	j;
	int	color_val;

	i = 0;
	while (i < 3)
	{
		if (!rgb[i])
			return (print_error("Missing RGB value"), 1);
		j = -1;
		if (!ft_isdigit(rgb[i][++j]))
			return (free(rgb), print_error("Invalid RGB value"), 1);
		color_val = ft_atoi(rgb[i]);
		if (color_val < 0 || color_val > 255)
		{
			free(rgb);
			return (print_error("Invalid RGB value"), 1);
		}
		color_array[i] = color_val;
		i++;
	}
	free_doble(rgb);
	return (0);
}

/*
	Extrae los valores RGB de la línea
	Llama a validate_and_assign_colors()
	Libera la memoria utilizada
*/
int	process_color_line(char *line, uint32_t *color_array)
{
	int		i;
	char	**rgb;

	i = 1;
	while (line[i] == ' ')
		i++;
	rgb = ft_split(line + i, ',');
	if (!rgb)
		return (1);
	if (validate_and_assign_colors(color_array, rgb))
		return (1);
	return (0);
}

/*
	Recorre el array text_walls en busca de las líneas de colores
	Llama a process_color_line()
	En caso de error, retorna 1
*/
int	color_check(t_data *data, char **text_walls)
{
	int	i;

	initialize_colors(data);
	i = 3;
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

/*
	Separa el texto en líneas con ft_split()
	Extrae rutas de texturas y las almacena en path_text_walls
	Usa mlx_load_png() para cargar las texturas en NO, SO, EA y WE
	Llama a color_check() para procesar los colores del techo y el suelo
*/
int	load_textures(t_data *data, char *textures)
{
	int		i;
	int		j;
	char	**text_walls;
	char	**path_text_walls;

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
	if (save_texture_wall(data, path_text_walls))
		return (1);
	if (color_check(data, text_walls))
		return (1);
	free_doble(text_walls);
	free_doble(path_text_walls);
	return (0);
}
