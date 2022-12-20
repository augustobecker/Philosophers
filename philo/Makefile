# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acesar-l <acesar-l@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/08 19:19:25 by acesar-l          #+#    #+#              #
#    Updated: 2022/12/18 06:01:27 by acesar-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	philo

COMPILER 	=	gcc -g
CFLAGS 		= 	-Wall -Wextra -Werror
CLEANUP 	= 	rm -rf

ASSEMBLY	=	-S

PTHREAD		=	-pthread

SRCS 		=	philosophers.c			\
				initial_validations.c	\
				initialize.c			\
				utils.c					\
				actions.c				\
				logs.c					\
				philosopher_dinner.c	\
				the_dinner_must_go_on.c	\
				time_utils.c			\
				error.c					\
				learning_pthreads.c

GREEN		=	\033[0;32m
RED			=	\033[0;31m
RESET		=	\033[0m

all:			$(NAME)

$(NAME):
				@$(COMPILER) $(PTHREAD) $(CFLAGS) $(SRCS) -o $(NAME)
				@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

clean:
				@$(CLEANUP) $(NAME)

fclean: 		clean
				@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:				fclean $(NAME)

run:			
				./$(NAME) 1 2 3 4 5

rerun:			re run

assembly:		
				$(COMPILER) $(ASSEMBLY) $(SRCS)
				@echo "$(GREEN)Assembly files were created$(RESET)"

.PHONY:			all clean fclean re run rerun assembly