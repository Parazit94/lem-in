/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:13:10 by vferry            #+#    #+#             */
/*   Updated: 2019/04/09 15:10:55 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	push_start(int *way, t_ways *buff, int *j, int i)
{
	ft_printf("L%d-%s ", g_inf.rooms[way[i]].num_ant, g_inf.rooms[way[i - 1]].name);
	buff->c_ant--;
	g_inf.rooms[way[i - 1]].ant++;
	g_inf.rooms[way[i - 1]].num_ant = g_inf.rooms[way[i]].num_ant;
	g_inf.rooms[way[i]].num_ant = g_inf.num_ants;
	g_inf.num_ants++;
	*j = 1;
}

static void	push_ant(int *way, int *j, int i)
{
	ft_printf("L%d-%s ", g_inf.rooms[way[i]].num_ant, g_inf.rooms[way[i - 1]].name);
	g_inf.rooms[way[i - 1]].num_ant = g_inf.rooms[way[i]].num_ant;
	g_inf.rooms[way[i - 1]].ant++;
	g_inf.rooms[way[i]].ant--;
	g_inf.rooms[way[i]].num_ant = 0;
	*j = 1;
}

static int	push(int *way, int size, t_ways *buff)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (i < size)
	{
		if (way[i] == g_inf.r_start)
		{
			if (buff->c_ant > 0 && g_inf.rooms[way[i - 1]].ant == 0
			&& g_inf.rooms[way[i - 1]].num_ant == 0)
			push_start(way, buff, &j, i);
		}
		else
		{
			if (g_inf.rooms[way[i]].num_ant > 0 && g_inf.rooms[way[i]].ant != 0)
				push_ant(way, &j, i);
		}
		i++;
	}
	return (j);
}

void		walk(void)
{
	int		i;
	int		j;

	j = 1;
	while (j)
	{
		j = 0;
		i = 0;
		while (i < g_inf.sample[g_inf.sam].count)
		{
			j += push(g_inf.sample[g_inf.sam].way[i].way,
			g_inf.sample[g_inf.sam].way[i].w, 
			&g_inf.sample[g_inf.sam].way[i]);
			i++;
		}
		if (j)
			ft_printf("\n");
	}
}
