CFLAGS = -Wall -Wextra -Werror
BONUS = philo_bonus
SOURCES = philo_bonus.c utils1.c ft_atoi.c utils2.c

all: $(NAME)

bonus: ${BONUS}

${BONUS}:
	gcc $(CFLAGS) $(SOURCES) -o ${BONUS}
	
clean:
	rm -f $(BONUS) 

fclean: clean
	rm -f $(BONUS)

re: fclean bonus
