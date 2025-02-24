/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/24 17:48:44 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

int	save_textures(t_data *data, char **splt, char **tmp, int i)
{
	int	j;

	j = 2;
	while (splt[i][j] == ' ' || (splt[i][j] >= 9 && splt[i][j] <= 13))
		j++;
	*tmp = ft_strdup(splt[i] + j);
	if (!*tmp)
		return (1);
	if (!ft_strncmp(splt[i], "NO ", 3))
		data->no = mlx_load_png(*tmp);
		else if (!ft_strncmp(splt[i], "SO ", 3))
		data->so = mlx_load_png(*tmp);
	else if (!ft_strncmp(splt[i], "WE ", 3))
		data->we = mlx_load_png(*tmp);
	else if (!ft_strncmp(splt[i], "EA ", 3))
		data->ea = mlx_load_png(*tmp);
	return (0);
}

int	texture_check(t_data *d, char **text)
{
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		if ((ft_strncmp(d->line, "NO", 2) || ft_strncmp(d->line, "SO", 2)
				|| ft_strncmp(d->line, "WE", 2) || ft_strncmp(d->line, "EA", 2))
			&& (d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))
		{
			*text = gnl_ft_strjoin(*text, d->line);
			d->texture_count++;
		}
		else if ((ft_strncmp(d->line, "F ", 2) || ft_strncmp(d->line, "C ", 2))
			&& (d->line[1] == ' ' || (d->line[1] >= 9 && d->line[1] <= 13)))
		{
			*text = gnl_ft_strjoin(*text, d->line);
			d->texture_count++;
		}
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	if (d->texture_count != 6)
		return (free(*text), free(d->line),
			printf("Error: Missing textures\n"), 1);
	if (save_map(d))
		return (free(*text), 1);
	return (close(d->fd), 0);
}

void	initialize_colors(t_data *data)  //SE QUEDA
{
	data->ceiling = malloc(sizeof(uint32_t) * 3);
	data->floor = malloc(sizeof(uint32_t) * 3);
	if (!data->ceiling || !data->floor)
		return ;
	ft_memset(data->ceiling, 0, sizeof(uint32_t) * 3);
	ft_memset(data->floor, 0, sizeof(uint32_t) * 3);
}


int	color_check(t_data *d, char *tmp, char *split, int coma)
{
	int		i;
	int		j;
	char	**color;

	i = 0;
	initialize_colors(d);
	while (tmp && tmp[i++])
		if (tmp[i] == ',')
			coma++;
	color = ft_split(tmp, ',');
	i = -1;
	while (color && color[++i])
	{
		j = -1;
		while (color[i][++j])
			if (!ft_isdigit(color[i][j]))
				return (free_triple(&color), printf("Error: RGB not digit\n"), 1);
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0
			|| coma != 2)
			return (free_triple(&color), printf("Error: Wrong RGB\n"), 1);
	}
	if (ft_strncmp(split, "C ", 2) == 0)
		d->ceiling1 = color;
	else if (ft_strncmp(split, "F ", 2) == 0)
		d->floor1 = color;
	return (0);
}

int	load_textures(t_data *data, char *textures)
{
	int		i;
	int		j;
	char	**splt;
	char	*tmp;
	
	i = -1;
	splt = ft_split(textures, '\n');
	tmp = NULL;
	while (splt && splt[++i])
	{
		j = i;
		while (splt[++j])
			if (!ft_strncmp(splt[i], splt[j], 2))
				return (free_triple(&splt), free(textures), free(data->line),
					print_error("Duplicated textures\n"), 1);
		if (splt[i][j])
		{
			if (save_textures(data, splt, &tmp, i))
				return (free_triple(&splt), free(tmp), free(textures), 1);
			if ((!ft_strncmp(splt[i], "C ", 2) || !ft_strncmp(splt[i], "F ", 2))
				&& color_check(data, tmp, splt[i], 0) == 1)
				return (1);
		}
	}
	data->ceiling[0] = ft_atoi(data->ceiling1[0]);
	data->ceiling[1] = ft_atoi(data->ceiling1[1]);
	data->ceiling[2] = ft_atoi(data->ceiling1[2]);
	data->floor[0] = ft_atoi(data->floor1[0]);
	data->floor[1] = ft_atoi(data->floor1[1]);
	data->floor[2] = ft_atoi(data->floor1[2]);
	return (free_doble(splt), free(textures), 0);
}
