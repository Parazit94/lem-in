/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:16:50 by vferry            #+#    #+#             */
/*   Updated: 2019/04/09 13:09:36 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		diff(t_sample *s, t_ways *buff, int i)
{
	while (i < buff->w)
	{
		if (s->touch[buff->way[i]] == 1 && buff->way[i] != g_inf.r_end
		&& buff->way[i] != g_inf.r_start)
			return (0);
		i++;
	}
	return (1);
}

void	put_way(t_sample *s, t_ways *buff, int i, int j)
{
	while (i < buff->w)
	{
		if (j == 1)
			s->touch[buff->way[i]] = 1;
		else if (i != g_inf.r_start)
			s->touch[buff->way[i]] = 0;
		i++;
	}
}

void	try_to_add(int	i, t_ways *buff, int *a, int *t)
{
	int		j;

	j = 0;
	if (diff(&g_inf.sample[i], buff, 0))
	{
		g_inf.sample[g_inf.c_sample].way = malloc(sizeof(t_ways) * 100);
		while (j < g_inf.sample[i].count)
		{
			g_inf.sample[g_inf.c_sample].way[j] = g_inf.sample[i].way[j];
			j++;
		}
		g_inf.sample[g_inf.c_sample].way[j] = *buff;
		g_inf.sample[g_inf.c_sample].count = g_inf.sample[i].count + 1;
		g_inf.sample[g_inf.c_sample].ok = 0;
		g_inf.sample[g_inf.c_sample].w += buff->w;
		ft_memcpy(g_inf.sample[g_inf.c_sample].touch, g_inf.sample[i].touch, g_inf.c_room);
		put_way(&g_inf.sample[g_inf.c_sample], buff, 0, 1);
		g_inf.c_sample++;
		*a = 1;
	}
	(*t)++;
}

void	vote_pick(t_sample *p, int *min, int i)
{
	if (p->count)
		p->w = p->w / p->count;
	if (p->count > g_inf.t)
	{
		*min = p->w;
		g_inf.sam = i;
		g_inf.t = p->count;
	}
	else if (p->count == g_inf.t && p->w < *min)
	{
		*min = p->w;
		g_inf.sam = i;
		g_inf.t = p->count;
	}
}

void	add_start(t_sample *p)
{
	int		i;

	i = 0;
	while (i < p->count)
	{
		p->way[i].way[p->way[i].w] = g_inf.r_start;
		p->way[i].w++;
		i++;
	}
}

void	put_count(t_sample *p)
{
	int		i;
	int		j;
	t_ways	*buff;

	i = 0;
	while (i < g_inf.c_ant)
	{
		buff = NULL;
		j = 0;
		while (j < p->count)
		{
			if (!buff || (buff && p->way[j].w + p->way[j].c_ant
			< buff->w + buff->c_ant))
				buff = &p->way[j];
			j++;
		}
		buff->c_ant++;
		i++;
	}
	g_inf.rooms[g_inf.r_start].num_ant = g_inf.num_ants++;
}

void	pick3(void)
{
	int		i;
	t_ways	*buff;
	int		min;

	i = 0;
	min = 2147483647;
	while (i < g_inf.c_sample)
	{
		buff = g_inf.w_ready;
		while (buff)
		{
			if (diff(&g_inf.sample[i], buff, 0))
			{
				g_inf.sample[i].way[g_inf.sample[i].count] = *buff;
				g_inf.sample[i].count++;
				put_way(&g_inf.sample[i], buff, 0, 1);
			}
			buff = buff->next;
		}
		vote_pick(&g_inf.sample[i], &min, i);
		i++;
	}
	add_start(&g_inf.sample[g_inf.sam]);
	put_count(&g_inf.sample[g_inf.sam]);
}

void	pick_2(void)
{
	int		i;
	t_ways	*buff;
	int		t;
	int		a;
	int		j;

	i = 0;
	while (i < g_inf.c_sample)
	{
		buff = g_inf.w_ready;
		a = 0;
		t = 0;
		if (g_inf.sample[i].ok == 0)
			while (buff && t < R && g_inf.sample[i].count < 4)
			{
				try_to_add(i, buff, &a, &t);
				buff = buff->next;
			}
		if (!a && g_inf.sample[i].ok == 0)
			g_inf.sample[i].ok = 1;
		i++;
	}
}

void	pick(void)
{
	int		i;
	int		j;
	t_ways	*buff;

	i = 0;
	buff = g_inf.w_ready;
	while (buff && i < R)
	{
		g_inf.sample[g_inf.c_sample].way = malloc(sizeof(t_ways) * 100);
		g_inf.sample[g_inf.c_sample].way[0] = *buff;
		g_inf.sample[g_inf.c_sample].count = 1;
		g_inf.sample[g_inf.c_sample].ok = 0;
		g_inf.sample[g_inf.c_sample].w = 0;
		g_inf.sample[g_inf.c_sample].w += buff->w;
		ft_bzero(g_inf.sample[g_inf.c_sample].touch, g_inf.c_room);
		j = 0;
		while (j < buff->w)
		{
			g_inf.sample[g_inf.c_sample].touch[buff->way[j]] = 1;
			j++;
		}
		g_inf.c_sample++;
		buff = buff->next;
		i++;
	}
	pick_2();
	pick3();
}