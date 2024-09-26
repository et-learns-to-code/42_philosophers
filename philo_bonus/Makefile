NAME = philo_bonus

SRC = args_check.c death.c init.c main.c philo_actions.c \
	philo_routine.c simulation.c time.c utils.c

OBJ = ${SRC:.c=.o}

CC = cc -g3 -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
