/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ne_nugen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:16:00 by vferry            #+#    #+#             */
/*   Updated: 2019/04/09 15:48:52 by vferry           ###   ########.fr       */
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
		ft_printf("[%d]: ", j);
		while (i < lol->w)
		{
			ft_printf("%d\t", lol->way[i]);
			i++;
		}
		ft_printf("\nw = %d\n", lol->w);
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
		ft_printf("c_room[%d] = %d\n", i, lol->w);
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

void	print_pick(void)
{
	int	i;
	int	j;
	int	k;
	int	lol;

	i = 0;
	lol = 0;
	ft_printf("c_sample = %d\n", g_inf.c_sample);
	while (i < g_inf.c_sample)
	{
		j = 0;
		if (g_inf.sample[i].ok == 1)
		{
			lol++;
			ft_printf("[%d]: count = %d\t ok = %d\n", lol, g_inf.sample[i].count, g_inf.sample[i].ok);
			while (j < g_inf.sample[i].count)
			{
				k = 0;
				while (k < g_inf.sample[i].way[j].w)
				{
					ft_printf("%d\t",  g_inf.sample[i].way[j].way[k]);
					k++;
				}
				ft_printf("\n");
				j++;
			}
		}
		i++;
	}
	ft_printf("sam = %d\n", g_inf.sam);
}

void	print_voted(int	a)
{
	int		i;
	int		j;
	int		lol;

	i = 0;
	lol = 0;
	while (i < g_inf.sample[a].count)
	{
		j = 0;
		ft_printf("c_ants = %d ", g_inf.sample[a].way[i].c_ant);
		ft_printf("[%d]: ", i);
		while (j < g_inf.sample[a].way[i].w)
		{
			ft_printf("%d\t", g_inf.sample[a].way[i].way[j]);
			j++;
		}
		ft_printf("w = %d", g_inf.sample[a].way[i].w);
		lol += j;
		ft_printf("\n");
		i++;
	}
	ft_printf("lol = %d\n", lol);
}