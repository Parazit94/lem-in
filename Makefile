NAME = lem-in
SRCS = $(wildcard srcs/*.c)
OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))
INCL = includes/
LIBFT_INC = libft/includes
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

objs/%.o: srcs/%.c
	gcc -c $< -o $@ -I $(INCL)

$(NAME): $(OBJS)
	make -C libft/
	gcc -O3 -o $(NAME) $(OBJS) -I$(INCL) -L libft -lft

clean:
	/bin/rm -f $(OBJS)
	make -C libft/ clean

fclean: clean
	/bin/rm -f $(NAME)
	make -C libft/ fclean

re: fclean all