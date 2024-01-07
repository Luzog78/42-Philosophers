/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:18 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/07 07:39:36 by ysabik           ###   ########.fr       */
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

# define USLEEP	10

typedef long long		t_ll;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_error
{
	NONE,
	PROCESS_END,
	ARGC_ERROR,
	ARG_ERROR,
	MALLOC_ERROR,
	THREAD_ERROR,
	PROCESS_ERROR,
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
	t_ll			last_meal;
	pthread_mutex_t	mutex;
}	t_philo;


typedef struct s_fork
{
	int				id;
	t_bool			used_by_left;
	t_bool			used_by_right;
	pthread_mutex_t	mutex;
	pthread_mutex_t	var_mutex;
}	t_fork;

typedef struct s_data
{
	int				nb_philo;
	t_ll			time_to_die;
	t_ll			time_to_eat;
	t_ll			time_to_sleep;
	int				nb_meal;
	t_fork			*fork;
	t_philo			*philo;
	t_ll			start;
	t_sim_state		state;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_args
{
	t_data	*data;
	int		id;
}	t_args;

void		*ft_calloc(size_t count, size_t size);
int			ft_error(t_error err, t_data *data);
void		ft_free_data(t_data *data);
t_ll		ft_get_time(t_data *data);
void		ft_init_data(t_data *data);
int			ft_init_simulation(t_data *data);
int			ft_parse(t_data *data, int ac, char **av);
void		*ft_philo(void *arg);
void		*ft_print(void *arg);
void		ft_print_action(t_data *data, int id, t_action action);
void		ft_print_broadcast(t_data *data, char *str);
char const	*ft_print_get_nth(int nth);
void		ft_print_timestamp(t_ll timestamp);
void		ft_reset_last_meal(t_data *data, t_philo *philo);
int			ft_start(t_data *data);
void		ft_usleep(t_ll time);
void		ft_set_data_state(t_data *data, t_sim_state state);
t_sim_state	ft_get_data_state(t_data *data);
void		ft_set_philo_state(t_philo *philo, t_state state);
t_state		ft_get_philo_state(t_philo *philo);
t_ll		ft_get_last_meal(t_philo *philo);
int			ft_get_fork_use(t_fork *fork, t_bool use_mutex);
void		ft_set_fork_use(t_fork *fork, int use, t_bool use_mutex);

#endif
