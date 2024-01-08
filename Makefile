# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 04:09:47 by ysabik            #+#    #+#              #
#    Updated: 2024/01/08 16:18:11 by ysabik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					= gcc
CFLAGS				= -Werror -Wall -Wextra -g
M_NAME				= philo
B_NAME				= philo_bonus
M_INCLUDES			= ./mandatory
B_INCLUDES			= ./bonus
M_SRC_FILES			= \
						mandatory/ft_calloc.c \
						mandatory/ft_error.c \
						mandatory/ft_free_data.c \
						mandatory/ft_get_data_state.c \
						mandatory/ft_get_fork_use.c \
						mandatory/ft_get_last_meal.c \
						mandatory/ft_get_philo_state.c \
						mandatory/ft_get_time.c \
						mandatory/ft_init_data.c \
						mandatory/ft_init_simulation.c \
						mandatory/ft_parse.c \
						mandatory/ft_philo.c \
						mandatory/ft_print_action.c \
						mandatory/ft_print_broadcast.c \
						mandatory/ft_print_get_nth.c \
						mandatory/ft_print_timestamp.c \
						mandatory/ft_reset_last_meal.c \
						mandatory/ft_set_data_state.c \
						mandatory/ft_set_fork_use.c \
						mandatory/ft_set_philo_state.c \
						mandatory/ft_start.c \
						mandatory/ft_usleep.c \
						mandatory/main.c
B_SRC_FILES			= \
						bonus/ft_calloc.c \
						bonus/ft_error.c \
						bonus/ft_free_data.c \
						bonus/ft_get_time.c \
						bonus/ft_init_data.c \
						bonus/ft_init_simulation.c \
						bonus/ft_kill.c \
						bonus/ft_parse.c \
						bonus/ft_philo.c \
						bonus/ft_print_action.c \
						bonus/ft_print_broadcast.c \
						bonus/ft_print_get_nth.c \
						bonus/ft_print_timestamp.c \
						bonus/ft_start.c \
						bonus/ft_usleep.c \
						bonus/main.c
						
M_OBJ_FILES			= $(M_SRC_FILES:.c=.o)
B_OBJ_FILES			= $(B_SRC_FILES:.c=.o)

all : $(M_NAME)

$(M_NAME) : $(M_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(M_NAME) $(M_OBJ_FILES) -I . -I $(M_INCLUDES)

bonus : $(B_OBJ_FILES)
	$(CC) $(CFLAGS) -o $(B_NAME) $(B_OBJ_FILES) -I . -I $(B_INCLUDES)
#bonus:
#	@echo "Bonus not implemented yet"

.c.o :
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(M_OBJ_FILES) $(B_OBJ_FILES)

fclean : clean
	rm -rf $(M_NAME) $(B_NAME)

re : fclean all

.PHONY : all bonus clean fclean re
