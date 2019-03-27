#include "lem-in.h"

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
            ft_strdel(&str);
            exit (1);
        }
    ft_strdel(&str);
    if (tmp != 0)
        g_info.c_ant = tmp;
    else
        exit (1);
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

    buff = str;
    if (!(str))
        return ;
    g_info.rooms[g_info.c_room].name = lem_split(str, ' ');
    ft_strchr(buff, ' ');
    g_info.rooms[g_info.c_room].x = ft_atoi(buff + 1);
    ft_strchr(buff, ' ');
    g_info.rooms[g_info.c_room].y = ft_atoi(buff + 1);
    g_info.rooms[g_info.c_room].s_or_e = c;
    g_info.c_room++;
    ft_strdel(&str);
}

void    print_rooms(void)
{
    int     i;

    i = 0;
    ft_printf("ants = %d\n", g_info.c_ant);
    ft_printf("c_room = %d\n", g_info.c_room);
    while (i < ROOM && g_info.rooms[i].name != NULL)
    {
        ft_printf("name = %s\nx = %d\ty = %d\tind = %d\n",
        g_info.rooms[i].name,  g_info.rooms[i].x,
        g_info.rooms[i].y,  g_info.rooms[i].s_or_e);
        i++;
    }
}

void    parsing2(char *line)
{
    char    **buff;

    if (!line)
        return ;
    if (g_info.connect == NULL)
        create_con();
    buff = ft_strsplit(line, '-');
}

void    parsing(void)
{
    char    *line;

    get_next_line(0, &line);
    parse_ants(line);
    while (get_next_line(0, &line) > 0)
        if (ft_strcmp(line, "##start") == 0)
        {
            ft_strdel(&line);
            get_next_line(0, &line);
            take_room(line, 1);
        }
        else if (ft_strcmp(line, "##end") == 0)
        {
            ft_strdel(&line);
            get_next_line(0, &line);
            take_room(line, 2);
        }
        else if (check_room(line) == 1)
            break ;
        else
            take_room(line, 0);
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
        g_info.rooms[i].name = NULL;
        i++;
    }
}

int main(int argc, char **argv)
{
    init();
    parsing();
    return (0);
}