/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ne_nugen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:16:00 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 21:18:39 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_one_way(void)
{
	int		i;

	i = 0;
	ft_printf("w = %d\n", g_inf.w_ready->w);
	while (i < g_inf.w_ready->w + 1 && g_inf.w_ready->way[i] != -1)
	{
		ft_printf("name = %s\n", g_inf.rooms[g_inf.w_ready->way[i]].name);
		i++;
	}
}

void	print_crowd(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_inf.c_ways)
	{
		ft_printf("way[%d]:\n", i + 1);
		j = 0;
		while (j < 2)
		{
			ft_printf("name[%d] = %s\t", j, g_inf.rooms[g_inf.w_heap[i].way[j]].name);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_opt(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_inf.count_ways)
	{
		j = 0;
		while (j < g_inf.go_ways[i].w)
		{
			ft_printf("%d\t", g_inf.go_ways[i].way[j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("\n\n");
}

void	print_touch(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_inf.c_ways)
	{
		j = 0;
		while (j < g_inf.c_ways)
		{
			ft_printf("%d\t", g_inf.touch[i][j]);
			j++;
		}
		ft_printf("\t%d\t%d", g_inf.c_touch[i], g_inf.c_average[i]);
		ft_printf("\n");
		i++;
	}
}

void	print_ways()
{
	int		i;
	int		j;
	t_ways	*lol;

	lol = g_inf.w_ready;
	j = 0;
	while (lol)
	{
		i = 0;
		while (i < lol->w)
		{
			ft_printf("%d\t", lol->way[i]);
			i++;
		}
		ft_printf("\n");
		lol = lol->next;
		j++;
	}
	ft_printf("c_ways = %d\n", j);
}

void	print_rooms(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_printf("ants = %d\n", g_inf.c_ant);
	ft_printf("c_room = %d\nr_st = %d\tr_end = %d\n", g_inf.c_room, g_inf.r_start,
	g_inf.r_end);
	while (i < ROOM && g_inf.rooms[i].name != NULL)
	{
		ft_printf("name = %s\nx = %d\ty = %d\tind = %d\tweight = %d\n",
		g_inf.rooms[i].name,  g_inf.rooms[i].x,
		g_inf.rooms[i].y,  g_inf.rooms[i].s_or_e, g_inf.rooms[i].weight[0]);
		i++;
	}
	i = 0;
	ft_printf("\t");
	while (i < g_inf.c_room)
	{
		j = 0;
		while (j < g_inf.c_room && i == 0)
		{
			ft_printf("\033[32m%s\t\033[m", g_inf.rooms[j].name);
			j++;
		}
		if (i == 0)
			ft_printf("\n");
		j = 0;
		while (j < g_inf.c_room)
		{
			if (j == 0)
				ft_printf("\033[32m%s\t\033[m", g_inf.rooms[i].name);
			ft_printf("%d\t", g_inf.connect[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_tail(void)
{
	int		i;

	i = 0;
	ft_printf("\n\ntail = \t");
	while (g_inf.tail[i] != -1)
	{
		ft_printf("%d  ", g_inf.tail[i]);
		i++;
	}
	ft_printf("\n\n");
}

void	print_way(void)
{
	t_ways	*lol;
	int		i;
	int		j;

	lol = g_inf.w_heap;
	i = 0;
	while (lol)
	{
		j = 0;
		ft_printf("c_room[%d] = %d\n", i, lol->c_rom);
		while (lol->way[j] != -1)
		{
			ft_printf("room[%d] = %d - ", j, lol->way[j]);
			ft_printf("%s\t\t", g_inf.rooms[lol->way[j]].name);
			j++;
		}
		ft_printf("\n");
		lol = lol->next;
		i++;
	}
}
