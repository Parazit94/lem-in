/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 16:16:50 by vferry            #+#    #+#             */
/*   Updated: 2019/04/06 20:30:44 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add(t_sample *p, t_ways *buff)
{
	int		i;

	i = 0;
	g_inf.sample[g_inf.c_sample].way = malloc(sizeof(t_ways) * 100);
	while (i < p->count && i < 100)
	{
		g_inf.sample[g_inf.c_sample].way[i] = p->way[i];
		i++;
	}
	ft_memcpy(g_inf.sample[g_inf.c_sample].touch, p->touch, g_inf.c_room);
	g_inf.sample[g_inf.c_sample].way[i] = *buff;
	g_inf.sample[g_inf.c_sample].count = p->count + 1;
	g_inf.sample[g_inf.c_sample].w = p->w + buff->w;
	g_inf.sample[g_inf.c_sample].ok = 0;
	g_inf.c_sample++;
}

void	polo(t_sample *p, t_ways *buff, int last)
{
	int		i;

	i = 0;
	while (i < last)
	{
		p->touch[buff->way[i]] = 0;
		i++;
	}
}

int		try_to_add(t_sample *p, t_ways *buff)
{
	int		i;

	i = 0;
	while (i < p->count)
	{
		if (&p->way[i] == buff)
			return (0);
		i++;
	}
	i = 1;
	while (i < buff->w)
	{
		if (p->touch[buff->way[i]] == 1)
		{
			polo(p, buff, i);
			return (0);
		}
		p->touch[buff->way[i]] = 1;
		i++;
	}
	add(p, buff);
	return (1);
}

void	add_new_way(t_sample *p)
{
	t_ways	*buff;

	buff = g_inf.w_ready;
	while (buff)
	{
		if (try_to_add(p, buff) == 1)
			return ;
		buff = buff->next;
	}
	p->ok = 1;
}

void	pick_2(void)
{
	int		i;

	i = 0;
	while (i < g_inf.c_sample)
	{
		add_new_way(&g_inf.sample[i]);
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
		j = 0;
		g_inf.sample[g_inf.c_sample].way = malloc(sizeof(t_ways) * 100);
		g_inf.sample[g_inf.c_sample].way[0] = *buff;
		while (j < buff->w)
		{
			g_inf.sample[g_inf.c_sample].touch[buff->way[j]] = 1;
			j++;
		}
		g_inf.sample[g_inf.c_sample].count = 1;
		g_inf.sample[g_inf.c_sample].ok = 0;
		g_inf.sample[g_inf.c_sample].w = 0;
		g_inf.sample[g_inf.c_sample].w += buff->w;
		g_inf.c_sample++;
		buff = buff->next;
		i++;
	}
	pick_2();
}