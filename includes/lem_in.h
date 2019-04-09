/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:11 by vferry            #+#    #+#             */
/*   Updated: 2019/04/09 15:11:57 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define ROOM 10000
# define W2 3
# define R 22
# include "./../libft/includes/libft.h"

typedef struct		s_ways
{
	int				w;
	int				c_rom;
	int				way[ROOM];
	int				a;
	int				num;
	int				c_ant;
	struct s_ways	*next;
}					t_ways;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				ant;
	int				num_ant;
	char			s_or_e;
	int				weight[2];
}					t_room;

typedef struct		s_sample
{
	t_ways			*way;
	int				count;
	char			ok;
	int				w;
	char			touch[ROOM];
}					t_sample;
typedef struct		s_lem
{
	int				c_ant;
	int				c_room;
	int				r_start;
	int				r_end;
	t_room			rooms[ROOM];
	int				tail[ROOM];
	int				c_ways;
	t_ways			*w_heap;
	t_ways			*w_ready;
	char			**connect;
	int				count_ways;
	int				num_ants;
	int				t;

	t_sample		sample[99999999];
	int				c_sample;
	int				sam;
}					t_lem;
t_lem				g_inf;

void				init(void);
void				parsing(void);
void				create_con(void);
void				take_con(char *line);
int					check_room(char *str);
void				take_room(char *str, char c, int i);
char				*lem_split(char *line, char c);
int					number(char c);
void				look_way(void);
void				get_ways(void);
void				for_one(void);
int					less_weight(int src);
void				for_one1(void);
void				for_crowd(void);
void				up_tail(t_ways **head, t_ways *cur);
t_ways				*new_way(int from, int weight);
t_ways				*take_tail(t_ways **head);
void				way_built(t_ways *buff);
int					repeat(int *way, int room, int size);
t_ways				*copy_way(t_ways *buff, int room);
void				way_destroy(t_ways *buff);
void				pick(void);
void				try_to_add(int	i, t_ways *buff, int *a, int *t);
void				vote_pick(t_sample *p, int *min, int i);
void				add_start(t_sample *p);
void				put_count(t_sample *p);
void				put_way(t_sample *s, t_ways *buff, int i, int j);
int					diff(t_sample *s, t_ways *buff, int i);
void				walk(void);
void				ft_clean(char	*str, int i);
//Не нужны
void				print_one_way(void);
void				print_crowd(void);
void				print_touch(void);
void				print_opt(void);
void				print_rooms(void);
void				print_tail(void);
void				print_way(void);
void				print_ways();
void				print_pick(void);
void				print_voted(int	a);
#endif
