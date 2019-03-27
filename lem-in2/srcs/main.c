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

    if (g_info.connect)
        ft_clean_con(g_info.connect);
    while (g_info.rooms)
    {
        buff = g_info.rooms;
        g_info.rooms = g_info.rooms->next;
        free(buff);
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
    while (str[i])
    {
        if (str[i] == '-')
            return (1);
        if (str[i] == ' ')
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

void    take_room(char *str, char c)
{
    char    *buff;

    buff = str;
    ft_strdel(&str);
}

void    parse(void)
{
    char    *line;
    int     i;
    char    c;

    get_next_line(0, &line);
    parse_ants(line);
    i = 0;
    while (get_next_line(0, &line) > 0)
    {
        c = 0;
        if (ft_strcmp(line, "##start\n") == 0)
            c = 1;
        else if (check_room(line) == 1)
            break ;
        else
            take_room(line, c);
    }
    
}

void    init(void)
{
    int     i;

    i = 0;
    g_info.connect = NULL;
    while (i < ROOM)
    {
        g_info.rooms[i].name = NULL;
        i++;
    }
}

int main(int argc, char **argv)
{
    init();
    parse();
    return (0);
}