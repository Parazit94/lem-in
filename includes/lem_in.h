/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferry <vferry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:05:11 by vferry            #+#    #+#             */
/*   Updated: 2019/04/06 21:19:13 by vferry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define ROOM 10000
# define W2 2
# define R 10000
# include "./../libft/includes/libft.h"

typedef struct		s_ways
{
	int				w;
	int				c_rom;
	int				way[ROOM];
	int				a;
	int				num;
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
	char			*is_touch;
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
	char			**touch;
	int				*c_touch;
	int				*c_average;
	int				count_ways;
	t_ways			*go_ways;
	int				num_ants;

	t_sample		sample[99999999];
	int				c_sample;
	int				sam;
}					t_lem;
t_lem				g_inf;
void				init(void);
void				walk2(void);
int					put_in_actual(t_ways *actual, int c_touch);
void				find_average(void);
void				take_optimal(int opt);
void				find_optimal(void);
void				fresh_ways(void);
void				get_ways(void);
void				look_way(void);
void				for_crowd(void);
void				for_one(void);
void				up_tail(t_ways **head, t_ways *cur);
t_ways				*new_way(int from, int weight);
t_ways				*take_tail(t_ways **head);
t_ways				*copy_way(t_ways *buff, int room);
void				way_built(t_ways *buff);
void				take_ways(void);
void				for_one1(void);
char				*lem_split(char *line, char c);
int					number(char c);
int					check_room(char *str);
void				create_con(void);
void				way_destroy(t_ways *buff);
int					less_weight(int src);
int					repeat(int *way, int room, int size);
void				take_con(char *line);
void				take_room(char *str, char c, int i);
void				parsing2(char *line);
void				parsing(void);
void				ft_clean(char	*str, int i);

void	pick(void);


void				create(void);
void	set_dif(t_sample *p, t_ways *buff, int i, int one);
int		cmp_ways(t_sample *p, t_ways *buff, int i);
void	way_diff(int i, t_ways *buff, int *a, int *tn);
void	set_sample_a(t_sample *buff, int val);
int		get_inc(int inc, int new_c);
int		set_param(int *max, int *sum, int *new_c, t_sample *buff);
int		get_weight(t_sample *buff);
void	take_sample(int i, int *min);


//Не нужны
void				print_one_way(void);
void				print_crowd(void);
void				print_touch(void);
void				print_opt(void);
void				print_rooms(void);
void				print_tail(void);
void				print_way(void);
void				print_ways();
void	print_pick(void);
#endif
