/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:15 by vferry            #+#    #+#             */
/*   Updated: 2019/03/31 18:02:34 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void    print_crowd(void)
{
	int     i;
	int     j;

	i = 0;
	while (i < g_info.c_ways)
	{
		ft_printf("way[%d]:\n", i + 1);
		j = 0;
		while (j < 2)
		{
			ft_printf("name[%d] = %s\t", j, g_info.rooms[g_info.w_heap[i].way[j]].name);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void    print_one_way(void)
{
	int     i;

	i = 0;
	while (i < ROOM && g_info.w_heap->way[i] != -1)
	{
		ft_printf("name = %s\n", g_info.rooms[g_info.w_heap->way[i]].name);
		i++;
	}
}

int     less_weight(int src)
{
	int     dst;
	int     i;

	i = 0;
	dst = src;
	if (src == g_info.r_end)
		return (-1);
	while (i < g_info.c_room)
	{
		if (g_info.connect[src][i] != 0 && i != g_info.r_start)
			if (g_info.rooms[i].weight[0] < g_info.rooms[dst].weight[0])
				dst = i;
		i++;
	}
	return (dst);
}

void    for_one(void)
{
	int     dst;

	g_info.w_heap = malloc(sizeof(t_ways));
	g_info.w_heap->way[0] = g_info.r_start;
	g_info.rooms[g_info.r_start].weight[0] = ROOM * 2;
	g_info.w_heap->c_rom++;
	while ((dst = less_weight(g_info.w_heap->way[g_info.w_heap->c_rom - 1])) >= 0)
	{
		g_info.w_heap->way[g_info.w_heap->c_rom] = dst;
		g_info.w_heap->c_rom++;
	}
	g_info.w_heap->way[g_info.w_heap->c_rom] = -1;
	print_one_way();
}

void	up_tail(t_ways **head, t_ways *cur)
{
	t_ways	*buff;

	buff = *head;
	if (!cur)
		return ;
	while (buff && buff->next)
		buff = buff->next;
	if (!buff)
		*head = cur;
	else
		buff->next = cur;
	if (*head == g_info.w_ready)
		g_info.c_ready++;
	else
		g_info.c_heap++;
}

t_ways	*new_way(int from, int weight)
{
	t_ways	*new;

	new = malloc(sizeof(t_ways));
	new->w = weight;
	new->way[0] = from;
	new->way[1] = -1;
	new->next = NULL;
	return (new);
}

t_ways	*take_tail(t_ways **head)
{
	t_ways	*buff;

	if (!*head)
		return (NULL);
	buff = *head;
	*head = (*head)->next;
	return (buff);
}

int		repeat(int *way, int room, int size)
{
	int i;

	i = 0;
	while (i < size)
		if (way[i] == room)
			return (0);
		else
			i++;
	return (1);
}

t_ways	*copy_way(t_ways *buff, int room)
{
	t_ways *new;
	int		i;
	int		j;

	new = malloc(sizeof(t_ways));
	new->w = buff->w + 1;
	new->way[0] = room;
	i = 0;
	j = 1;
	while (j < ROOM && i < ROOM && buff->way[i] != -1)
	{
		new->way[j] = buff->way[i];
		i++;
		j++;
	}
	new->way[j] = -1;
	new->next = NULL;
	return (new);
}

void	way_built(t_ways *buff)
{
	int		i;

	i = 0;
	while (i < g_info.c_room)
	{
		if (g_info.connect[buff->way[0]][i] > 0 && i != buff->way[0]
		&& repeat(buff->way, i, buff->w + 1) == 1 && (((g_info.rooms[buff->way[0]].weight[0] >
		g_info.rooms[i].weight[0] || g_info.rooms[i].weight[1] < W2)
		&& g_info.rooms[buff->way[0]].weight[0] != -1) || buff->way[0] == g_info.r_start))
		{
			g_info.rooms[i].weight[1]++;
			if (i == g_info.r_end)
				up_tail(&g_info.w_ready, copy_way(buff, i));
			else
				up_tail(&g_info.w_heap, copy_way(buff, i));
		}
		i++;
	}
}

void	way_destroy(t_ways *buff)
{
	if (buff)
		free(buff);
}

void	for_crowd(void)
{
	t_ways	*buff;

	up_tail(&g_info.w_heap, new_way(g_info.r_start, 0));
	g_info.c_heap++;
	while (g_info.w_heap)
	{
		buff = take_tail(&g_info.w_heap);
		g_info.c_heap--;
		if (buff == NULL)
			ft_error_clean();
		way_built(buff);
		way_destroy(buff);
	}
}

void    get_ways(void)
{
	if (g_info.c_ant < 2)
		for_one();
	else
		for_crowd();
}


void    look_way(void)
{
	int     i;
	int     j;
	int     k;

	i = 0;
	k = 0;
	g_info.tail[i] = g_info.r_end;
	g_info.rooms[g_info.r_end].weight[0] = 0;
	while (g_info.tail[i] >= 0)
	{
		j = 0;
		while (j < g_info.c_room)
		{
			if (g_info.connect[g_info.tail[i]][j] == 1 && j != g_info.r_start
			&& g_info.rooms[j].weight[0] == -1)
			{
				g_info.connect[j][g_info.tail[i]] = 2;
				g_info.connect[g_info.tail[i]][j] = 2;
				k++;
				g_info.tail[k] = j;
				g_info.rooms[j].weight[0] = g_info.rooms[g_info.tail[i]].weight[0] + 1;
			}
			j++;
		}
		i++;
	}
	// print_tail();
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
	g_info.rooms[g_info.c_room].weight[0] = -1;
	g_info.rooms[g_info.c_room].weight[1] = -1;
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
		else if (line[0] == '#')
		{
			ft_strdel(&line);
			continue ;
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
	// print_rooms();
}

void    init(void)
{
	int     i;

	i = 0;
	g_info.connect = NULL;
	g_info.c_room = 0;
	g_info.c_heap = 0;
	g_info.c_ready = 0;
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
	get_ways();
	print_ways();
	return (0);
}

void	print_ways()
{
	int		i;
	int		j;
	t_ways	*lol;

	lol = g_info.w_ready;
	j = 0;
	while (lol)
	{
		i = 0;
		while (i < lol->w)
		{
			ft_printf("%d\t", lol->way[i]);
			i++;
		}
		ft_printf("\n");
		lol = lol->next;
		j++;
	}
	ft_printf("c_ways = %d\n", j);
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
		g_info.rooms[i].y,  g_info.rooms[i].s_or_e, g_info.rooms[i].weight[0]);
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

void    print_way(void)
{
	t_ways *lol;
	int     i;
	int     j;
	
	lol = g_info.w_heap;
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