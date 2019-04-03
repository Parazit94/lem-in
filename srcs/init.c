/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:15:50 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 16:19:22 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    init(void)
{
	int     i;

	i = 0;
    g_inf.c_ant = 0;
	g_inf.c_room = 0;
    g_inf.r_start = -1;
    g_inf.r_end = -1;
	g_inf.c_ways = 0;
    g_inf.w_heap = NULL;
    g_inf.w_ready = NULL;
	g_inf.connect = NULL;
    g_inf.touch = NULL;
    g_inf.c_touch = NULL;
    g_inf.c_average = NULL;
    g_inf.count_ways = 0;
    g_inf.go_ways = NULL;
	g_inf.num_ants = 0;
	while (i < ROOM)
	{
		g_inf.tail[i] = -1;
		g_inf.rooms[i].name = NULL;
		i++;
	}
}