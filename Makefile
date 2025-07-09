CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
all: $(NAME) clean

$(NAME): $(OBJS)
	@cc -o $(NAME) $^

clean:
	@rm -rf $(OBJS)
fclean: clean
	@rm -rf $(NAME)
re: fclean all
