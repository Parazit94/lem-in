/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:23:54 by vferry            #+#    #+#             */
/*   Updated: 2019/04/06 16:16:03 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_dif(t_sample *p, t_ways *buff, int i, int one)
{
	if (i < buff->w)
	{
		if (one)
			p->r[buff->way[i]] = 1;
		else
		{
			if (i != g_inf.r_start)
				p->r[buff->way[i]] = 0;
		}
		set_dif(p, buff, i + 1, one);
	}
}

int		cmp_ways(t_sample *p, t_ways *buff, int i)
{
	if (i < buff->w)
	{
		if (p->r[buff->way[i]] == 1 && buff->way[i] != g_inf.r_start
			&& buff->way[i] != g_inf.r_end)
			return (0);
		else
			return (cmp_ways(p, buff, i + 1));
	}
	return (1);
}

void	way_diff(int i, t_ways *buff, int *a, int *tn)
{
	int		j;

	if (cmp_ways(&g_inf.sample[i], buff, i))
	{
		j = 0;
		while (j < g_inf.sample[i].count)
		{
			g_inf.sample[g_inf.c_sample].way[j] = g_inf.sample[i].way[j];
			j++;
		}
		g_inf.sample[g_inf.c_sample].way[j] = *buff;
		g_inf.sample[g_inf.c_sample].ok = 0;
		g_inf.sample[g_inf.c_sample].w = 0;
		g_inf.sample[g_inf.c_sample].count = g_inf.sample[i].count + 1;
		ft_memcpy(g_inf.sample[g_inf.c_sample].r, g_inf.sample[i].r, ROOM);
		set_dif(&g_inf.sample[g_inf.c_sample], buff, 0, 1);
		g_inf.c_sample++;
		*a = 1;
	}
	(*tn)++;
}

void	set_sample_a(t_sample *buff, int val)
{
	int		i;

	i = 0;
	while (i < buff->count)
		buff->way[i++].a = val;
}

int		get_inc(int inc, int new_c)
{
	if (inc == 0)
	{
		if (g_inf.c_ant % new_c == 0)
			inc = g_inf.c_ant / new_c;
		else
			inc = (g_inf.c_ant / new_c) + 1;
	}
	else
	{
		if ((g_inf.c_ant - inc) % new_c == 0)
			inc = ((g_inf.c_ant - inc) / new_c);
		else
			inc = ((g_inf.c_ant - inc) / new_c) + 1;
	}
	return (inc);
}

int		set_param(int *max, int *sum, int *new_c, t_sample *buff)
{
	int		i;
	int		i_max;

	i_max = 0;
	i = 0;
	*sum = 0;
	(*new_c)--;
	while (i < buff->count)
	{
		if (buff->way[i].a == 0)
		{
			(*sum) += buff->way[i].w;
			if (buff->way[i].w > *max)
			{
				*max = buff->way[i].w;
				i_max = i;
			}
		}
		i++;
	}
	return (i_max);
}

int		get_weight(t_sample *buff)
{
	int		sum;
	int		max;
	int		new_c;
	int		i_max;

	new_c = buff->count + 1;
	set_sample_a(buff, 0);
	while (1)
	{
		max = buff->way[0].w;
		i_max = set_param(&max, &sum, &new_c, buff);
		if (g_inf.c_ant >= max * new_c - sum || new_c == 1)
			break ;
		if (i_max == -1)
			return (100000);
		if (g_inf.c_ant < max * new_c - sum)
			buff->way[i_max].a = -1;
	}
	set_sample_a(buff, 0);
	return (max - 1 + get_inc(max * new_c - sum, new_c));
}

void	take_sample(int i, int *min)
{
	g_inf.sample[i].w = get_weight(&g_inf.sample[i]);
	if (g_inf.sample[i].w < *min)
	{
		*min = g_inf.sample[i].w;
		g_inf.sam = i;
	}
}

void	create3(void)
{
	int		i;
	int		min;
	int		ind;
	t_ways	*buff;

	i = 0;
	min = 1000000;
	ind = 0;
	while (i < g_inf.c_sample)
	{
		buff = g_inf.w_ready;
		while (buff)
		{
			if (cmp_ways(&g_inf.sample[i], buff, 1))
			{
				g_inf.sample[i].way[g_inf.sample[i].count] = *buff;
				g_inf.sample[i].count++;
				set_dif(&g_inf.sample[i], buff, 0, 1);
			}
			buff = buff->next;
		}
		take_sample(i, &min);
		i++;
	}
}

void	create2(int count)
{
	int		i;
	int		a;
	int		tn;
	t_ways	*buff;

	i = 0;
	while (i < g_inf.c_sample)
	{
		buff = g_inf.w_ready;
		a = 0;
		tn = 0;
		while (buff && tn < count)
		{
			way_diff(i, buff, &a, &tn);
			buff = buff->next;
		}
		if (!a && g_inf.sample[i].ok == 0)
			g_inf.sample[i].ok = 1;
		i++;
	}
}


void	create(void)
{
	int		i;
	int		c;
	t_ways	*buff;

	c = 0;
	buff = g_inf.w_ready;
	while (buff)
	{
		g_inf.sample[g_inf.c_sample].way = malloc(sizeof(t_ways) * g_inf.c_ways);
		g_inf.sample[g_inf.c_sample].way[0] = *buff;
		g_inf.sample[g_inf.c_sample].count = 1;
		g_inf.sample[g_inf.c_sample].ok = 0;
		g_inf.sample[g_inf.c_sample].w = 0;
		ft_bzero(&g_inf.sample[g_inf.c_sample], ROOM);
		i = 0;
		while (i < buff->w)
			g_inf.sample[g_inf.c_sample].r[buff->way[i++]] = 1;
		g_inf.c_sample++;
		buff = buff->next;
		c++;
	}
	create2(c);
}