NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -pthread
RM = rm -rf
SRCS = main.c actions.c checker.c init.c philo.c utils.c
SRC = $(addprefix ./src/,$(SRCS))
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re debug

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re