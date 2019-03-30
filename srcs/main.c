/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:15 by vferry            #+#    #+#             */
/*   Updated: 2019/03/30 17:44:27 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void    print_way(void)
{
    t_ways *lol;
    int     i;
    int     j;
    
    lol = g_info.ways;
    i = 0;
    while (lol)
    {
        j = 0;
        ft_printf("c_room[%d] = %d\n", i, lol->c_rom);
        while (lol->way[j] != -1)
        {
            ft_printf("room[%d] = %d - ", j, lol->way[j]);
            ft_printf("%s\t\t", g_info.rooms[lol->way[j]].name);
            j++;
        }
        ft_printf("\n");
        lol = lol->next;
        i++;
    }
}


void    look_way(void)
{
    int     i;
    int     j;
    int     k;
    int     lol;
    int     next;
    t_ways  *head;
    t_ways  *buff;
    t_ways  *buff2;

    i = 0;
    k = 0;
    g_info.tail[i] = g_info.r_end;
    g_info.ways = malloc(sizeof(t_ways));
    g_info.ways->way[0] = g_info.tail[i];
    g_info.ways->way[1] = -1;
    g_info.ways->prev = NULL;
    g_info.ways->next = NULL;
    g_info.ways->c_rom = 1;
    head = g_info.ways;
    while (g_info.tail[i] >= 0)
    {
        j = 0;
        next = 0;
        // k = i;
        while (j < g_info.c_room)
        {
            buff = head;
            buff2 = buff;
            if (g_info.connect[g_info.tail[i]][j] == 1 && j != g_info.r_start && g_info.rooms[j].weight == 0)
            {
                next++;
                if (next >= 2)
                {
                    while (buff->next)
                        buff = buff->next;
                    while (buff2)
                        if (buff2->c_rom - 2 >=0 && buff2->way[buff2->c_rom - 2] == g_info.tail[i])
                            break ;
                        else
                            buff2 = buff2->next;
                    buff->next = malloc(sizeof(t_ways));
                    buff->next->prev = buff;
                    buff->next->next = NULL;
                    lol = 0;
                    while (lol < buff2->c_rom - 1)
                    {
                        buff->next->way[lol] = buff2->way[lol];
                        lol++;
                    }
                    buff->next->way[lol] = j;
                    buff->next->way[lol + 1] = -1;
                    buff->next->c_rom = lol + 1;
                }
                buff = head;
                while (buff)
                {
                    if (buff->way[buff->c_rom - 1] == g_info.tail[i])
                    {
                        buff->way[buff->c_rom] = j;
                        buff->way[buff->c_rom + 1] = -1;
                        buff->c_rom++;
                        break ;
                    }
                    buff = buff->next;
                }
                g_info.connect[j][g_info.tail[i]] = 2;
                // while (g_info.tail[k] != -1)
                k++;
                g_info.tail[k] = j;
                g_info.rooms[j].weight = g_info.rooms[g_info.tail[i]].weight + 1;
            }
            j++;
        }
        i++;
    }
    print_tail();
    // print_rooms();
    print_way();
}


////////PARSING/////////////////

void    ft_clean_con(char **arr)
{
    int     i;

    i = 0;
    while (i < g_info.c_room)
    {
        ft_strdel(&arr[i]);
        i++;
    }
    free(arr);
}

void    ft_error_clean(void)
{
    t_room  *buff;
    int     i;

    i = 0;
    if (g_info.connect)
        ft_clean_con(g_info.connect);
    while (i < ROOM && g_info.rooms[i].name)
    {
        free(g_info.rooms[i].name);
        i++;
    }
    ft_printf("ERROR");
    exit (1);
}

int		number(char c)
{
	return (!(c >= 48 && c <= 57));
}

void    parse_ants(char *str)
{
    int     i;
    int     tmp;

    i = 0;
    tmp = 0;
    while (str[i])
        if (number(str[i]) == 0)
        {
            tmp += str[i] - 48;
			if (number(str[i + 1]) == 0)
				tmp *= 10;
			i++;
        }
        else
        {
            ft_printf("ANTS no right");
            ft_strdel(&str);
            exit (1);
        }
    ft_strdel(&str);
    if (tmp != 0)
        g_info.c_ant = tmp;
    else
    {
        ft_printf("NO ANTS");
        exit (1);
    }
}

int     check_room(char *str)
{
    int     i;
    int     p;

    i = 0;
    p = 0;
    if (str[0] == '#')
    {
        ft_strdel(&str);
        get_next_line(0, &str);
        check_room(str);
    }
    else
        while (str[i])
        {
            if (str[i] == '-')
                return (1);
            else if (str[i] == ' ')
                p++;
            if (p > 2)
            {
                ft_strdel(&str);
                ft_error_clean();
            }
            i++;
       }
    return (0);
}

char    *lem_split(char *line, char c)
{
    int     i;
    int     j;
    char    *str;

    i = 0;
    j = 0;
    while (line[i] && line[i] != c)
        i++;
    str = (char *)malloc(sizeof(char) * i + 1);
    while (j < i)
    {
        str[j] = line[j];
        j++;
    }
    str[j] = 0;
    return (str);
}

void    take_room(char *str, char c)
{
    char    *buff;
    int     tmp;
    int     i;

    if (!(str))
        return ;
    g_info.rooms[g_info.c_room].name = lem_split(str, ' ');
    if (!(buff = ft_strchr(str, ' ')))
        ft_error_clean();
    buff++;
    tmp = 0;
    i = 0;
    while (buff[i])
    {
        if (number(buff[i]) == 0)
        {
            tmp += buff[i] - 48;
			if (number(buff[i + 1]) == 0)
				tmp *= 10;
        }
        else if (buff[i] == ' ')
        {
            g_info.rooms[g_info.c_room].x = tmp;
            tmp = 0;
        }
        else
            ft_error_clean();
        i++;
    }
    g_info.rooms[g_info.c_room].y = tmp;
    g_info.rooms[g_info.c_room].s_or_e = c;
    g_info.rooms[g_info.c_room].weight = 0;
    g_info.c_room++;
    ft_strdel(&str);
}

void    create_con(void)
{
    int     i;
    int     j;

    i = 0;
    g_info.connect = malloc(sizeof(char *) * g_info.c_room);
    while (i < g_info.c_room)
    {
        j = 0;
        g_info.connect[i] = malloc(sizeof(char) * g_info.c_room);
        while (j < g_info.c_room)
        {
            g_info.connect[i][j] = 0;
            j++;
        }
        i++;
    }
}

void    take_con(char *line)
{
    char    **buff;
    int     i;
    int     one;
    int     two;

    buff = ft_strsplit(line, '-');
    i = 0;
    one = -1;
    two = -1;
    while (i < ROOM && g_info.rooms[i].name)
    {
        if (ft_strcmp(buff[0], g_info.rooms[i].name) == 0)
            one = i;
        if (ft_strcmp(buff[1], g_info.rooms[i].name) == 0)
            two = i;
        i++;
    }
    ft_strdel(&buff[0]);
    ft_strdel(&buff[1]);
    free(buff);
    if (one == -1 || two == -1)
        ft_error_clean();
    g_info.connect[one][two] = 1;
    g_info.connect[two][one] = 1;
    ft_strdel(&line);
}

void    parsing2(char *line)
{
    if (!line)
        return ;
    if (g_info.connect == NULL)
        create_con();
    take_con(line);
    while (get_next_line(0, &line) > 0)
    {
        if (line[0] == '#')
            ft_strdel(&line);
        if (line && line[0] == '#' && line[1] == '#')
            ft_strdel(&line);
        if (line)
            take_con(line);
    }
}

void    parsing(void)
{
    char    *line;
    int     i;

    i = 0;
    get_next_line(0, &line);
    parse_ants(line);
    while (get_next_line(0, &line) > 0)
        if (ft_strcmp(line, "##start") == 0)
        {
            ft_strdel(&line);
            get_next_line(0, &line);
            g_info.r_start = g_info.c_room;
            take_room(line, 1);
            i++;
        }
        else if (ft_strcmp(line, "##end") == 0)
        {
            ft_strdel(&line);
            get_next_line(0, &line);
            g_info.r_end = g_info.c_room;
            take_room(line, 2);
            i++;
        }
        else if (check_room(line) == 1)
            break ;
        else
            take_room(line, 0);
    if (i != 2)
    {
        ft_strdel(&line);
        ft_error_clean();
    }
    parsing2(line);
    print_rooms();
}

void    init(void)
{
    int     i;

    i = 0;
    g_info.connect = NULL;
    g_info.c_room = 0;
    while (i < ROOM)
    {
        g_info.tail[i] = -1;
        g_info.rooms[i].name = NULL;
        i++;
    }
    while (i < ROOM)
    {
        g_info.tail[i] = -1;
        i++;
    }
}

int main(int argc, char **argv)
{
    init();
    parsing();
    look_way();
    return (0);
}

void    print_rooms(void)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    ft_printf("ants = %d\n", g_info.c_ant);
    ft_printf("c_room = %d\nr_st = %d\tr_end = %d\n", g_info.c_room, g_info.r_start, g_info.r_end);
    while (i < ROOM && g_info.rooms[i].name != NULL)
    {
        ft_printf("name = %s\nx = %d\ty = %d\tind = %d\tweight = %d\n",
        g_info.rooms[i].name,  g_info.rooms[i].x,
        g_info.rooms[i].y,  g_info.rooms[i].s_or_e, g_info.rooms[i].weight);
        i++;
    }
    i = 0;
    ft_printf("\t");
    while (i < g_info.c_room)
    {

        j = 0;
        while (j < g_info.c_room && i == 0)
        {
            ft_printf("\033[32m%s\t\033[m", g_info.rooms[j].name);
            j++;
        }
        if (i == 0)
            ft_printf("\n");
        j = 0;
        while (j < g_info.c_room)
        {
            if (j == 0)
                ft_printf("\033[32m%s\t\033[m", g_info.rooms[i].name);
            ft_printf("%d\t", g_info.connect[i][j]);
            j++;
        }
        ft_printf("\n");
        
        i++;
    }
}

void    print_tail(void)
{
    int     i;

    i = 0;
    ft_printf("\n\ntail = \t");
    while (g_info.tail[i] != -1)
    {
        ft_printf("%d  ", g_info.tail[i]);
        i++;
    }
    ft_printf("\n\n");
}