/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:11 by vferry            #+#    #+#             */
/*   Updated: 2019/03/28 20:09:22 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H
#define ROOM 10000
# include "./../libft/includes/libft.h"

typedef struct  s_ways
{
    int         w;
    int         way[ROOM];
}               t_ways;

typedef struct  s_room
{
    char        *name;
    int         x;
    int         y;
    char        s_or_e;
    int         weight;
}               t_room;

typedef struct  s_lem
{
    int         c_ant;
    int         c_room;
    int         r_start;
    int         r_end;
    t_room      rooms[ROOM];
    int         tail[10000];
    t_ways      ways[9999];
    char        **connect;
}               t_lem;
static t_lem    g_info;

void        print_rooms(void);

#endif