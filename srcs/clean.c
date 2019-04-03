/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:46:58 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 21:28:16 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	clean_heap(t_ways *del)
{
	t_ways *buff;

	while (del)
	{
		buff = del;
		del = del->next;
		free(buff);
	}
}

static void	clean_connect(char **del, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		free(del[i]);
		i++;
	}
	free(del);
}

static void	clean_room(void)
{
	int i;

	i = 0;
	while (i < g_inf.c_room)
	{
		free(g_inf.rooms[i].name);
		free(g_inf.rooms[i].is_touch);
		i++;
	}
}

void		ft_clean(char *str, int i)
{
	if (g_inf.c_room != 0)
		clean_room();
	if (g_inf.w_heap)
		clean_heap(g_inf.w_heap);
	if (g_inf.w_ready)
		clean_heap(g_inf.w_ready);
	if (g_inf.go_ways)
		clean_heap(g_inf.w_heap);
	if (g_inf.connect)
		clean_connect(g_inf.connect, g_inf.c_room);
	if (g_inf.touch)
		clean_connect(g_inf.touch, g_inf.c_ways);
	if (g_inf.c_touch)
		free(g_inf.c_touch);
	if (g_inf.c_average)
		free(g_inf.c_average);
	if (str)
		ft_printf("%s\n", str);
	if (i == 1)
		exit(1);
}
