/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:53:25 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/27 16:10:34 by pausanch         ###   ########.fr       */
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

int	color_check(t_data *d, char *tmp, char *split, int coma)
{
	int		i;
	int		j;
	char	**color;

	i = 0;
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
				return (free_doble(color), print_error("RGB not digit"), 1);
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0
			|| coma != 2)
			return (free_doble(color), print_error("Wrong RGB"), 1);
	}
	if (ft_strncmp(split, "C ", 2) == 0)
		d->ceiling1 = color;
	else if (ft_strncmp(split, "F ", 2) == 0)
		d->floor1 = color;
	return (0);
}

int	verify_and_save_textures(t_data *data, char **s, char **tmp, int i)
{
	int	j;

	j = i;
	while (s[++j])
		if (!ft_strncmp(s[i], s[j], 2))
			return (free_doble(s), print_error("Duplicated textures"), 1);
	if (save_textures(data, s, tmp, i))
		return (free_triple(&s), free(*tmp), 1);
	if ((!ft_strncmp(s[i], "C ", 2) || !ft_strncmp(s[i], "F ", 2))
		&& color_check(data, *tmp, s[i], 0) == 1)
		return (free_doble(s), free(*tmp), 1);
	return (0);
}

int	load_textures(t_data *data, char *textures, int i)
{
	char	*tmp;
	char	**s;

	i = -1;
	tmp = NULL;
	s = ft_split(textures, '\n');
	if (!s)
		return (free(textures), free(data->line), 1);
	while (s[++i])
	{
		if (verify_and_save_textures(data, s, &tmp, i))
			return (free(textures), 1);
		free(tmp);
	}
	if (data->ceiling1 && data->floor1)
		initialize_colors(data);
	return (atoi_color(data), free_doble(s), free(textures), 0);
}
