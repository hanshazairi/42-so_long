/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:27:34 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/09 21:23:39 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "so_long.h"
#include "libft/libft.h"
// #include "mlx.h"

static int	is_set(char *line, char *set)
{
	char			*tmp;
	size_t			i;
	const size_t	len = ft_strlen(line);

	i = 0;
	while (*line)
	{
		tmp = set;
		while (*tmp)
			if (*line == *tmp++)
				++i;
		++line;
	}
	if (i != len)
		return (0);
	return (1);
}

static int	is_ber(char *file)
{
	const char	*ext = ft_strrchr(file, '.');
	const int	len = ft_strlen(ext);

	if (!ft_strncmp(ext, ".ber", len))
		return (1);
	return (0);
}

static int	is_rectangular_and_cep(char *file, t_map *map)
{
	int			i;
	char		*line;
	const int	fd = open(file, O_RDONLY);

	i = 0;
	line = get_next_line(fd);
	while (line && ++i)
	{
		if (i == 1)
			map->cols = ft_strlen(line);
		else if (ft_strlen(line) != map->cols)
			map->diff_cols = 1;
		if (ft_strchr(line, 'C'))
			map->has_c = 1;
		if (ft_strchr(line, 'E'))
			map->has_e = 1;
		if (ft_strchr(line, 'P'))
			map->has_p = 1;
		free(line);
		line = get_next_line(fd);
	}
	map->rows = i;
	if (!map->has_c || !map->has_e || !map->has_p || map->diff_cols)
		return (0);
	return (1);
}

static int	is_valid_map(char *file, t_map *map)
{
	int			i;
	int			is_valid;
	char		*line;
	const int	fd = open(file, O_RDONLY);

	is_valid = 1;
	if (!is_ber(file) || !is_rectangular_and_cep(file, map))
		is_valid = 0;
	i = 0;
	line = get_next_line(fd);
	while (line && ++i)
	{
		if ((i == 1 || i == map->rows) && !is_set(line, "1"))
			is_valid = 0;
		else if (i != 1 && i != map->rows && (!is_set(line, "01CEP") \
				|| line[0] != '1' || line[map->cols - 1] != '1'))
			is_valid = 0;
		free(line);
		line = get_next_line(fd);
	}
	if (!is_valid)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	map;

	map.has_c = 0;
	map.has_e = 0;
	map.has_p = 0;
	map.diff_cols = 0;
	if (argc == 2 && is_valid_map(argv[1], &map))
		ft_putendl_fd("Valid map", 1);
	else
		ft_putendl_fd("Error", 2);
	return (0);
}
