/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:48:07 by pausanch          #+#    #+#             */
/*   Updated: 2025/02/19 16:59:35 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

int	fill_map(t_data *d)
{
	int		i;
	int		j;
	size_t	max_l;
	char	*new_ln;

	i = -1;
	max_l = ft_electric_bucleloo(d);
	while (d->map[++i])
	{
		j = ft_strlen(d->map[i]);
		new_ln = ft_calloc(1, max_l + 1);
		if (!new_ln)
			return (1);
		ft_strlcpy(new_ln, d->map[i], ft_strlen(d->map[i]) + 1);
		while ((size_t)j < max_l)
			new_ln[j++] = ' ';
		new_ln[j] = '\0';
		free(d->map[i]);
		d->map[i] = new_ln;
		d->height_map = i;
		d->width_map = max_l - 1;
	}
	return (0);
}

int	check_chars(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map && data->map[i])
	{
		while (data->map[i][j])
		{
			if (ft_bucle(data, i, j))
				return (1);
			j++;
		}
		j = 0;
		i++;
	}
	if (data->char_pos != 1)
		return (print_error("Invalid number of players"), 1);
	return (0);
}

void	ft_player_pos_ini(t_data *data, char c, int i, int j)
{
	if (c == 'O' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player->pos->x = (double)j + 0.5;
		data->player->pos->y = (double)i + 0.5;
	}
}

int	check_map(t_data *data)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	if (check_first_line(data) || check_chars(data) || fill_map(data))
		return (1);
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			c = data->map[i][j];
			if (((i == 0 || i == data->height_map) || (j == 0
						|| j == data->width_map)) && c != '1' && c != ' ')
				return (print_error("Map not closed"), 1);
			if (i != 0 && i != data->height_map && (c == '0' || c == 'N'
					|| c == 'S' || c == 'E' || c == 'W')
				&& ((data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' ')
				|| (data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')))
				return (print_error("Horizontal or vertical elements"), 1);
			ft_player_pos_ini(data, c, i, j);
		}
	}
	return (0);
}

int	save_map(t_data *data)
{
	char	*copy;

	copy = NULL;
	if (!data->line)
		return (print_error("No map"), 1);
	while (data->line)
	{
		copy = gnl_ft_strjoin2(copy, data->line);
		if (!copy)
			return (1);
		if (data->line[0] == '\n')
			return (free(copy), free(data->line), print_error("Format"), 1);
		free(data->line);
		data->line = get_next_line(data->fd);
	}
	close(data->fd);
	if (copy)
	{
		data->map = ft_split(copy, '\n');
		if (!data->map)
			return (free(copy), 1);
		if (check_map(data))
			return (free(copy), 1);
	}
	return (free(copy), 0);
}
