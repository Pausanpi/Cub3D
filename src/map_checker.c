/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pausanch <pausanch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:48:07 by pausanch          #+#    #+#             */
/*   Updated: 2025/01/29 12:35:25 by pausanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/cub3d.h"

int	fill_map(t_data *d)
{
	int i;
	int j;
	size_t	max_l;
	char	*new_ln;

	i = -1;
	max_l = 0;
	while (d->map[++i])
	{
		if (max_l < ft_strlen(d->map[i]))
			max_l = ft_strlen(d->map[i]);
	}
	i = -1;
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

int check_chars(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data->map && data->map[i])
    {
        while (data->map[i][j])
        {
            if (data->map[i][j] != '1' && data->map[i][j] != '0' \
                && data->map[i][j] != 'N' \
                && data->map[i][j] != 'S' && data->map[i][j] != 'E' \
                && data->map[i][j] != 'W' && data->map[i][j] != 32)
                return (printf("Error: Invalid character\n"), 1);
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' \
                || data->map[i][j] == 'E' || data->map[i][j] == 'W')
            {
                data->char_pos++;
                data->orientation = data->map[i][j];
            }
            j++;
        }
        j = 0;
        i++;
    }
    if (data->char_pos != 1)
        return (printf("Error: Invalid number of players\n"), 1);
    return (0);
}

int check_first_line(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (data->map && data->map[i])
    {
        while (i == 0 && (data->map[i][j] == 32 \
            || (data->map[i][j] >= 9 && data->map[i][j] <= 13)))
            j++;
        if (i == 0 && (data->map[i][j] != '1' \
            || data->map[i][ft_strlen(data->map[i]) - 1] != '1'))
            return (printf("Error: Space in first line\n"), 1);
        i++;
    }
    return (0);
}

int check_map(t_data *data)
{
	int	i;
	int	j;
	char c;

	i = -1;
    if (check_first_line(data) || check_chars(data) || fill_map(data))
	{
		return (1);			
	}
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			c = data->map[i][j];
			if (((i == 0 || i == data->height_map)
				|| (j == 0 || j == data->width_map)) && c != '1' && c != ' ')
				return (printf("Error: Map not closed\n"), 1);
			if (i != 0 && i != data->height_map
					&& (c == 'O' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				&& ((data->map[i - 1][j] == ' ' || data->map[i + 1][j] == ' ')
				|| (data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')))
				return (printf("Error: Horizontal or vertical elements\n"), 1);
			if (c == 'O' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				data->player->pos->x = (double)j;
				data->player->pos->y = (double)i;
			}
		}
	
	}
	return (0);
}

char	*gnl_ft_strjoin2(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	len3;
	char	*s3;
	int		i;

	if (s1 == NULL)
	{
		s1 = ft_calloc(1, sizeof (char));
		if (!s1)
			return (free (s1), s1 = NULL, NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = len1 + len2;
	i = len1;
	s3 = malloc((len3 + 1) * sizeof(char));
	if (s3 == 0)
		return (free (s1), s1 = NULL, NULL);
	ft_memcpy(s3, s1, len1);
	ft_memcpy(&s3[i], s2, (len2 + 1));
	return (free (s1), s1 = NULL, s3);
}

int	save_map(t_data *data)
{
	char	*copy;

	copy = NULL;
	if (!data->line)
		return(printf("Error: No map\n"), 1);
	while (data->line)
	{
		copy = gnl_ft_strjoin2(copy, data->line);
		if (!copy)
			return (1);
		if (data->line[0] == '\n')
            return (free(copy), free(data->line), printf("Error: Format\n"), 1);
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


int check_textures(t_data *data, char **texture)
{
    while (data->line && data->line[0] != '1' && data->line[0] != ' ')
    {
        if ((ft_strncmp(data->line, "NO", 2) || ft_strncmp(data->line, "SO", 2) \
            || ft_strncmp(data->line, "WE", 2) || ft_strncmp(data->line, "EA", 2)) \
            && (data->line[2] == ' ' || (data->line[2] >= 9 && data->line[3] <= 13)))
        {
            *texture = gnl_ft_strjoin2(*texture, data->line);
            data->texture_count++;
        }
        else if ((ft_strncmp(data->line, "F", 1) || ft_strncmp(data->line, "C", 1)) \
        && (data->line[1] == ' ' || (data->line[1] >= 9 && data->line[2] <= 13)))
        {
            *texture = gnl_ft_strjoin2(*texture, data->line);
            data->texture_count++;
        }

        free(data->line);
        data->line = get_next_line(data->fd);
		if (data->line[0] >= 9 && data->line[0] <= 13)
		{
			free(data->line);
			data->line = get_next_line(data->fd);
		}
    }
    if (data->texture_count != 6)
        return (free(*texture), free(data->line),
            printf("Error: Missing textures\n"), 1);
    if (save_map(data))
	{
        return (1);
	}
	return (0);
}
