/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:15 by vferry            #+#    #+#             */
/*   Updated: 2019/04/06 21:20:49 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	take_it(t_sample *p, int *c, int index)
{
	if (g_inf.sam < 0)
		g_inf.sam = index;
	else if (*c == p->count)
	{
		if (g_inf.sample[g_inf.sam].w > p->w)
		{
			g_inf.sam = index;
			*c = p->count;
		}
	}
	else if (*c < p->count && p->count <= g_inf.c_ant)
	{
		g_inf.sam = index;
		*c = p->count;
	}
}

void	vote_pick(void)
{
	int		i;
	int		min;
	int		count;

	i = 0;
	count = 0;
	min = 999999;
	while (i < g_inf.c_sample)
	{
		
		if (g_inf.sample[i].ok == 1 && g_inf.sample[i].count >= count)
		{
			g_inf.sample[i].w = g_inf.sample[i].w / g_inf.sample[i].count;
			take_it(&g_inf.sample[i], &count, i);
		}
		i++;
	}
}

void	print_push(char *room, int ant)
{
	ft_printf("L%d-%s ", ant, room);
}

void	push(int i, int j)
{
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j]].ant--;
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].ant++;
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].num_ant =
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j]].num_ant;
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j]].num_ant = 0;
	print_push(g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].name,
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].num_ant);
}

void	push_start(int i, int j)
{
	g_inf.rooms[g_inf.r_start].ant--;
	g_inf.num_ants++;
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].ant++;
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].num_ant = g_inf.num_ants;
	print_push(g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].name,
	g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j - 1]].num_ant);
}

void	push_ants(void)
{
	int		i;
	int		j;

	i = g_inf.sample[g_inf.sam].count - 1;
	while (i >= 0)
	{
		j = 1;
		while (j < g_inf.sample[g_inf.sam].way[i].w)
		{
			if (g_inf.rooms[g_inf.sample[g_inf.sam].way[i].way[j]].ant != 0)
				push(i, j);
			j++;
		}
		if ((i == 0 || g_inf.rooms[g_inf.r_start].ant + g_inf.sample[g_inf.sam].way[0].w - 1
		>= g_inf.sample[g_inf.sam].way[i].w) && g_inf.rooms[g_inf.r_start].ant > 0)
			push_start(i, j);
		i--;
	}
	ft_printf("\n");
}

void	walk(void)
{
	while (g_inf.rooms[g_inf.r_end].ant != g_inf.c_ant)
		push_ants();
}

int	main(int argc, char **argv)
{
	init();
	parsing();
	look_way();
	get_ways();
	// print_ways();
	// take_ways();
	pick();
	vote_pick();
	// print_pick();
	// create();
	// walk2();
	walk();
	ft_clean(NULL, 0);
	return (0);
}
