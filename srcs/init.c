/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:15:50 by vferry            #+#    #+#             */
/*   Updated: 2019/04/09 14:53:20 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init(void)
{
	int	i;

	i = 0;
	g_inf.c_ant = 0;
	g_inf.c_room = 0;
	g_inf.r_start = -1;
	g_inf.r_end = -1;
	g_inf.c_ways = 0;
	g_inf.w_heap = NULL;
	g_inf.w_ready = NULL;
	g_inf.connect = NULL;
	g_inf.count_ways = 0;
	g_inf.num_ants = 1;
	g_inf.c_sample = 0;
	g_inf.sam = -1;
	while (i < ROOM)
	{
		g_inf.tail[i] = -1;
		g_inf.rooms[i].name = NULL;
		i++;
	}
}
