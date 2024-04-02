# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 09:39:18 by skorbai           #+#    #+#              #
#    Updated: 2024/04/02 15:22:23 by skorbai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		init_params.c \
		utils.c \
		ft_itoa.c \
		init_philos.c \
		error.c \
		simulate.c

OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

%.o: %.c
	cc $(C_FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	cc $(C_FLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

tidymake: re
	make clean

san: $(OBJS)
	cc $(C_FLAGS) -fsanitize=address -g $(OBJS) -o san

thread: $(OBJS)
	cc $(C_FLAGS) -fsanitize=thread -g $(OBJS) -o thread

.PHONY: all clean fclean re tidymake san