/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:13:10 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 16:14:04 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_ants(int ant, char *room)
{
	ft_printf("L%d-%s ", ant, room);
}

static void	push_ants(void)
{
	int		i;
	int		j;

	i = g_inf.count_ways - 1;
	while (i >= 0)
	{
		j = 1;
		while (j < g_inf.go_ways[i].w)
		{
			if (g_inf.rooms[g_inf.go_ways[i].way[j]].ant != 0)
			{
				g_inf.rooms[g_inf.go_ways[i].way[j]].ant--;
				g_inf.rooms[g_inf.go_ways[i].way[j - 1]].ant++;
				g_inf.rooms[g_inf.go_ways[i].way[j - 1]].num_ant = g_inf.rooms[g_inf.go_ways[i].way[j]].num_ant;
				g_inf.rooms[g_inf.go_ways[i].way[j]].num_ant = 0;
				print_ants(g_inf.rooms[g_inf.go_ways[i].way[j - 1]].num_ant,
				g_inf.rooms[g_inf.go_ways[i].way[j - 1]].name);
			}
			j++;
		}
		if ((i == 0 || g_inf.rooms[g_inf.r_start].ant >= g_inf.go_ways[i].w ||
		(g_inf.rooms[g_inf.r_start].ant + g_inf.go_ways[0].w - 1) >= g_inf.go_ways[i].w)
		&& g_inf.rooms[g_inf.r_start].ant > 0)
		{
			g_inf.rooms[g_inf.r_start].ant--;
			g_inf.num_ants++;
			g_inf.rooms[g_inf.go_ways[i].way[j - 1]].ant++;
			g_inf.rooms[g_inf.go_ways[i].way[j - 1]].num_ant = g_inf.num_ants;
			print_ants(g_inf.rooms[g_inf.go_ways[i].way[j - 1]].num_ant,
			g_inf.rooms[g_inf.go_ways[i].way[j - 1]].name);
		}
		i--;
	}
	ft_printf("\n");
}

void	walk(void)
{
	while (g_inf.rooms[g_inf.r_end].ant != g_inf.c_ant)
		push_ants();
}