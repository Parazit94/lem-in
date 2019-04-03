/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taking.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:43:46 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 15:45:20 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    take_con(char *line)
{
	char    **buff;
	int     i;
	int     one;
	int     two;

	buff = ft_strsplit(line, '-');
	i = 0;
	one = -1;
	two = -1;
	while (i < ROOM && g_inf.rooms[i].name)
	{
		if (ft_strcmp(buff[0], g_inf.rooms[i].name) == 0)
			one = i;
		if (ft_strcmp(buff[1], g_inf.rooms[i].name) == 0)
			two = i;
		i++;
	}
	ft_strdel(&buff[0]);
	ft_strdel(&buff[1]);
	free(buff);
	if (one == -1 || two == -1)
		ft_error_clean();
	g_inf.connect[one][two] = 1;
	g_inf.connect[two][one] = 1;
	ft_strdel(&line);
}

void    take_room(char *str, char c)
{
	char    *buff;
	int     tmp;
	int     i;

	if (!(str))
		return ;
	g_inf.rooms[g_inf.c_room].name = lem_split(str, ' ');
	if (!(buff = ft_strchr(str, ' ')))
		ft_error_clean();
	buff++;
	tmp = 0;
	i = 0;
	while (buff[i])
	{
		if (number(buff[i]) == 0)
		{
			tmp += buff[i] - 48;
			if (number(buff[i + 1]) == 0)
				tmp *= 10;
		}
		else if (buff[i] == ' ')
		{
			g_inf.rooms[g_inf.c_room].x = tmp;
			tmp = 0;
		}
		else
			ft_error_clean();
		i++;
	}
	g_inf.rooms[g_inf.c_room].y = tmp;
	g_inf.rooms[g_inf.c_room].s_or_e = c;
	g_inf.rooms[g_inf.c_room].weight[0] = -1;
	g_inf.rooms[g_inf.c_room].weight[1] = -1;
	g_inf.rooms[g_inf.c_room].ant = 0;
	g_inf.rooms[g_inf.c_room].num_ant = -1;
	g_inf.c_room++;
	ft_strdel(&str);
}