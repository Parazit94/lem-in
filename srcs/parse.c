/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:42:46 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 15:46:27 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void    parse_ants(char *str)
{
	int     i;
	int     tmp;

	i = 0;
	tmp = 0;
	while (str[i])
		if (number(str[i]) == 0)
		{
			tmp += str[i] - 48;
			if (number(str[i + 1]) == 0)
				tmp *= 10;
			i++;
		}
		else
		{
			ft_printf("Count of ANTS is't right");
			ft_strdel(&str);
			exit (1);
		}
	ft_strdel(&str);
	if (tmp != 0)
		g_inf.c_ant = tmp;
	else
	{
		ft_printf("NO ANTS");
		exit (1);
	}
}

void    parsing2(char *line)
{
	if (!line)
		return ;
	if (g_inf.connect == NULL)
		create_con();
	take_con(line);
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '#')
			ft_strdel(&line);
		if (line && line[0] == '#' && line[1] == '#')
			ft_strdel(&line);
		if (line)
			take_con(line);
	}
}

void    parsing(void)
{
	char    *line;
	int     i;

	i = 0;
	get_next_line(0, &line);
	parse_ants(line);
	while (get_next_line(0, &line) > 0)
		if (ft_strcmp(line, "##start") == 0)
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			g_inf.r_start = g_inf.c_room;
			take_room(line, 1);
			i++;
		}
		else if (ft_strcmp(line, "##end") == 0)
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			g_inf.r_end = g_inf.c_room;
			take_room(line, 2);
			i++;
		}
		else if (line[0] == '#')
		{
			ft_strdel(&line);
			continue ;
		}
		else if (check_room(line) == 1)
			break ;
		else
			take_room(line, 0);
	if (i != 2)
	{
		ft_strdel(&line);
		ft_error_clean();
	}
	g_inf.rooms[g_inf.r_start].ant = g_inf.c_ant;
	parsing2(line);
	// print_rooms();
}