# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 19:19:25 by acesar-l          #+#    #+#              #
#    Updated: 2022/12/22 18:41:27 by acesar-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	philo_bonus

COMPILER 	=	gcc -g
CFLAGS 		= 	-Wall -Wextra -Werror
CLEANUP 	= 	rm -rf

PTHREAD		=	-pthread

SRCS 		=	philosophers_bonus.c	\
				initial_validations.c	\
				ft_atoi.c				\
				prepare_for_dinner.c	\
				start_dinner.c			\
				philosopher_dinner.c	\
				the_dinner_must_go_on.c	\
				actions.c				\
				logs.c					\
				time_utils.c

GREEN		=	\033[0;32m
RED			=	\033[0;31m
RESET		=	\033[0m

all:			$(NAME)

$(NAME):
				@$(COMPILER) $(PTHREAD) $(CFLAGS) $(SRCS) -o $(NAME)
				@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

clean:
				@$(CLEANUP) $(NAME)
				@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

fclean: 		clean

re:				fclean $(NAME)

.PHONY:			all clean fclean re