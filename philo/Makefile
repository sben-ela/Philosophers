CFLAGS = -Wall -Wextra -Werror
NAME = philo.a
PROG = philo

SOURCES = philosopher.c ft_atoi.c utils1.c utils2.c
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	cc $(CFLAGS) $(NAME) -o $(PROG)
clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME) $(PROG)
re: fclean all
