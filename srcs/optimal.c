/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:11:22 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 17:02:50 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		put_in_actual(t_ways *actual, int c_touch)
{
	int		i;

	i = 1;
	while (i < actual->w && actual->way[i] != -1)
	{
		if (g_inf.rooms[actual->way[i]].is_touch[c_touch] == 0)
		{
			g_inf.rooms[actual->way[i]].is_touch[c_touch] = 1;
			i++;
		}
		else
			return (1);
	}
	return (0);
}

void	find_average(void)
{
	int				i;
	int				j;
	t_ways			*buff;
	unsigned int	count;
	int				lol;

	i = 0;
	g_inf.c_average = malloc(sizeof(unsigned int) * g_inf.c_ways);
	while (i < g_inf.c_ways)
	{
		j = 0;
		count = 0;
		lol = 0;
		buff = g_inf.w_ready;
		while (j < g_inf.c_ways)
		{
			if (g_inf.touch[i][j] == 1)
				count += buff->w;
			j++;
			buff = buff->next;
		}
		if ((g_inf.c_average[i] = count - (count / g_inf.c_touch[i])) == 0)
			g_inf.c_average[i] = count;
		i++;
	}
}

void	take_optimal(int opt)
{
	int		i;
	int		j;
	t_ways	*buff;

	g_inf.go_ways = malloc(sizeof(t_ways) * g_inf.c_touch[opt]);
	i = 0;
	j = 0;
	buff = g_inf.w_ready;
	while (i < g_inf.c_ways)
	{
		if (g_inf.touch[opt][i] == 1)
		{
			g_inf.go_ways[j] = *buff;
			j++;
		}
		i++;
		buff = buff->next;
	}
	// print_opt();
}

void	find_optimal(void)
{
	int		i;
	int		max;
	int		opt;
	int		lol;

	i = 0;
	max = 0;
	opt = -1;
	lol = ROOM;
	while (i < g_inf.c_ways)
	{
		if (g_inf.c_touch[i] > max && lol > g_inf.c_average[i]
		&& max < g_inf.c_ant)
		{
			max = g_inf.c_touch[i];
			opt = i;
		}
		i++;
	}
	g_inf.count_ways = g_inf.c_touch[opt];
	// ft_printf("opt = %d\n", opt);
	take_optimal(opt);
}
