/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:18 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/06 15:27:16 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define USLEEP	0

typedef unsigned int		t_ui;
typedef long long			t_ll;
typedef unsigned long long	t_ull;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_error
{
	NONE = 0,
	ARGC_ERROR,
	ARG_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR,
	MUTEX_ERROR,
}	t_error;

typedef enum e_state
{
	READY,
	THINKING,
	EATING,
	SLEEPING,
	FULL,
}	t_state;

typedef enum e_sim_state
{
	PENDING,
	RUNNING,
	ENDED,
}	t_sim_state;

typedef enum e_action
{
	JOIN,
	THINK,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	EAT,
	RELEASE_LEFT_FORK,
	RELEASE_RIGHT_FORK,
	SLEEP,
	GET_FULL,
	DIE,
}	t_action;

typedef struct s_philo
{
	int				id;
	t_state			state;
	pthread_t		thread;
	int				nb_meal;
	struct timeval	last_meal;
}	t_philo;

typedef struct s_fork
{
	int				id;
	t_bool			used;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	t_fork			*fork;
	t_philo			*philo;
	pthread_mutex_t	print_mutex;
	struct timeval	start;
	t_sim_state		state;
}	t_data;

typedef struct s_args
{
	t_data	*data;
	int		id;
}	t_args;

void		*ft_calloc(size_t count, size_t size);
int			ft_error(t_error err, t_data *data);
void		ft_free_data(t_data *data);
int			ft_get_time(t_data *data);
int			ft_init(t_data *data);
int			ft_parse(t_data *data, int ac, char **av);
void		*ft_philo(void *arg);
void		ft_print_action(t_data *data, int id, t_action action);
void		ft_print_broadcast(t_data *data, char *str);
char const	*ft_print_get_nth(int nth);
void		ft_print_timestamp(t_data *data);
int			ft_start(t_data *data);
void		ft_init_data(t_data *data);

#endif
