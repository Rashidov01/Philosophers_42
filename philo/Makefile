# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arashido <arashido@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 17:56:16 by arashido          #+#    #+#              #
#    Updated: 2023/09/23 20:50:04 by arashido         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = 	philo.c \
		utils.c \
		time.c \
		actions.c \
		init.c \
		program.c \
		philo_actions.c

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g3

OBJ = $(addprefix obj/, $(SRC:.c=.o))

all: obj $(NAME)

obj/%.o: %.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

$(NAME): $(OBJ) philo.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re obj bonus