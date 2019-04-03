/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:46:58 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 16:47:24 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_clean_con(char **arr)
{
	int	i;

	i = 0;
	while (i < g_inf.c_room)
	{
		ft_strdel(&arr[i]);
		i++;
	}
	free(arr);
}

void	ft_error_clean(void)
{
	t_room	*buff;
	int		i;

	i = 0;
	if (g_inf.connect)
		ft_clean_con(g_inf.connect);
	while (i < ROOM && g_inf.rooms[i].name)
	{
		free(g_inf.rooms[i].name);
		i++;
	}
	ft_printf("ERROR");
	exit(1);
}
