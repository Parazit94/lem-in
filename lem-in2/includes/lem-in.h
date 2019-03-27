#ifndef LEM_IN_H
#define LEM_IN_H
#define ROOM 10000
# include "./../libft/includes/libft.h"

typedef struct  s_room
{
    char            *name;
    int             x;
    int             y;
    char            s_or_e;
}               t_room;

typedef struct  s_lem
{
    int     c_ant;
    int     c_room;
    t_room  rooms[ROOM];
    char    **connect;
}               t_lem;
t_lem   g_info;

#endif