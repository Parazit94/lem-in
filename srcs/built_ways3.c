/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ways3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:09:23 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 16:10:28 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	take_ways(void)
{
	t_ways	*buff;
	t_ways	*actual;
	int		i;
	int		j;
	int		count;

	i = 0;
	if (g_inf.c_ant == 1)
		return ;
	actual = g_inf.w_ready;
	g_inf.touch = malloc(sizeof(char * ) * g_inf.c_ways);
	g_inf.c_touch = malloc(sizeof(int) * g_inf.c_ways);
	while (i < g_inf.c_ways)
	{
		j = 0;
		g_inf.touch[i] = malloc(sizeof(char) * g_inf.c_ways);
		buff = g_inf.w_ready;
		put_in_actual(actual, i);
		while (buff)
		{
			if (buff == actual || put_in_actual(buff, i) == 0)
				g_inf.touch[i][j] = 1;
			else
				g_inf.touch[i][j] = 0;
			if (j < i)
				g_inf.touch[j][i] = g_inf.touch[i][j];
			buff = buff->next;
			j++;
		}
		actual = actual->next;
		i++;
	}
	i = 0;
	while (i < g_inf.c_ways)
	{
		j = 0;
		count = 0;
		while (j < g_inf.c_ways)
		{
			if (g_inf.touch[i][j] == 1)
				count++;
			j++;
		}
		g_inf.c_touch[i] = count;
		i++;
	}
	find_average();
	find_optimal();
	// print_touch();
}

void	for_one1(void)
{
	int		i;
	int		j;

	g_inf.w_ready = malloc(sizeof(t_ways));
	g_inf.w_ready->w = g_inf.w_heap->w;
	i = g_inf.w_ready->w;
	j = 0;
	while (i > 0)
	{
		g_inf.w_ready->way[j] = g_inf.w_heap->way[i];
		i--;
		j++;
	}
	g_inf.go_ways = g_inf.w_ready;
	g_inf.count_ways = 1;
	free(g_inf.w_heap);
}