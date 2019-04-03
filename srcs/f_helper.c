/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:47:49 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 16:14:48 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char    *lem_split(char *line, char c)
{
	int     i;
	int     j;
	char    *str;

	i = 0;
	j = 0;
	while (line[i] && line[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		str[j] = line[j];
		j++;
	}
	str[j] = 0;
	return (str);
}

int		number(char c)
{
	return (!(c >= 48 && c <= 57));
}

int     check_room(char *str)
{
	int     i;
	int     p;

	i = 0;
	p = 0;
	if (str[0] == '#')
	{
		ft_strdel(&str);
		get_next_line(0, &str);
		check_room(str);
	}
	else
		while (str[i])
		{
			if (str[i] == '-')
				return (1);
			else if (str[i] == ' ')
				p++;
			if (p > 2)
			{
				ft_strdel(&str);
				ft_error_clean();
			}
			i++;
	   }
	return (0);
}

void    create_con(void)
{
	int     i;
	int     j;

	i = 0;
	g_inf.connect = malloc(sizeof(char *) * g_inf.c_room);
	while (i < g_inf.c_room)
	{
		j = 0;
		g_inf.connect[i] = malloc(sizeof(char) * g_inf.c_room);
		while (j < g_inf.c_room)
		{
			g_inf.connect[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	way_destroy(t_ways *buff)
{
	if (buff)
		free(buff);
}