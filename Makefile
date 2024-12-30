# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pzaw <pzaw@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/30 20:23:00 by pzaw              #+#    #+#              #
#    Updated: 2024/12/30 20:23:00 by pzaw             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -pthread -fsanitize=thread
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
