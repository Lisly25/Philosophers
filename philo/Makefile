# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skorbai <skorbai@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/02 09:39:18 by skorbai           #+#    #+#              #
#    Updated: 2024/04/02 09:56:13 by skorbai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		init_params.c \
		utils.c

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

tidymake: re clean

san: $(OBJS)
	cc $(C_FLAGS) -fsanitize=address -fsanitize=thread -g $(OBJS) -o san

.PHONY: all clean fclean re tidymake san