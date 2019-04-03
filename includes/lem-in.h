/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:11 by vferry            #+#    #+#             */
/*   Updated: 2019/04/03 13:48:16 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H
#define ROOM 10000
#define W2 2
# include "./../libft/includes/libft.h"

typedef struct  s_ways
{
    int             w;
    int             c_rom;
    int             way[ROOM];
    struct s_ways   *next;
    struct s_ways   *in;
}               t_ways;

typedef struct  s_room
{
    char        *name;
    int         x;
    int         y;
    int         ant;
    int         num_ant;
    char        s_or_e;
    int         weight[2];
    char        *is_touch;
}               t_room;

typedef struct  s_lem
{
    int         c_ant;
    int         c_room;
    int         r_start;
    int         r_end;
    t_room      rooms[ROOM];
    int         tail[ROOM];
    int         c_ways;
    t_ways      *w_heap;
    t_ways      *w_ready;
    char        **connect;
    char        **touch;
    int         *c_touch;
    int         *c_average;
    int         count_ways;
    t_ways      *go_ways;
    int         num_ants;
}               t_lem;
static t_lem    g_info;

void        print_rooms(void);
void        print_tail(void);
void        print_way(void);
void        print_ways();
void        ft_error_clean(void);
#endif