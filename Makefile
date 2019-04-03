NAME = lem-in
SRCS = $(wildcard srcs/*.c)
OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
INCL = includes/
LIBFT_INC = libft/includes
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

objs/%.o: srcs/%.c
	gcc -I $(INCL) -c $< -o $@ 

$(NAME): $(OBJS)
	make -C libft/
	gcc -O3 -I$(INCL) -L libft -lft -o $(NAME) $(OBJS) 

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all