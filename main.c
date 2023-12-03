/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:21 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/04 00:35:03 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define USLEEP 100

/**
 * @returns	The time in milliseconds since the start of the simulation.
*/
int	ft_get_time(t_data *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - data->start.tv_sec) * 1000
		+ (current.tv_usec - data->start.tv_usec) / 1000);
}

void	ft_print_timestamp(t_data *data)
{
	int	ms;
	
	ms = ft_get_time(data);
	printf("[%02d:%02d:%02d:%03d] ", ms / 3600000, ms / 60000 % 60,
		ms / 1000 % 60, ms % 1000);
	//printf("[%09d] ", ms);
}

void	ft_print_broadcast(t_data *data, char *str)
{
	pthread_mutex_lock(&data->print_mutex);
	ft_print_timestamp(data);
	printf(">> %s <<\n", str);
	pthread_mutex_unlock(&data->print_mutex);
}

char const *ft_print_get_nth(int nth)
{
	if (nth % 10 == 1 && nth % 100 != 11)
		return ("st");
	else if (nth % 10 == 2 && nth % 100 != 12)
		return ("nd");
	else if (nth % 10 == 3 && nth % 100 != 13)
		return ("rd");
	else
		return ("th");
}

void	ft_print_action(t_data *data, int id, t_action action)
{
	pthread_mutex_lock(&data->print_mutex);
	ft_print_timestamp(data);
	printf("Philosopher %d ", id);
	if (action == JOIN)
		printf("is joining the table");
	else if (action == THINK)
		printf("is thinking");
	else if (action == TAKE_LEFT_FORK)
		printf("has taken his left fork");
	else if (action == TAKE_RIGHT_FORK)
		printf("has taken his right fork");
	else if (action == EAT)
		printf("is eating  (%d%s meal)", data->philo[id].nb_meal + 1, ft_print_get_nth(data->philo[id].nb_meal + 1));
	else if (action == RELEASE_LEFT_FORK)
		printf("has released his left fork");
	else if (action == RELEASE_RIGHT_FORK)
		printf("has released his right fork");
	else if (action == SLEEP)
		printf("is sleeping");
	else if (action == GET_FULL)
		printf("is full");
	else if (action == DIE)
		printf("died");
	printf("\n");
	pthread_mutex_unlock(&data->print_mutex);
}

void ft_free_data(t_data *data)
{
	if (data->philo)
		free(data->philo);
	if (data->fork)
		free(data->fork);
}

int	ft_error(t_error err, t_data *data)
{
	if (err == ARGC_ERROR)
		printf("Error: Wrong number of arguments\n");
	else if (err == ARG_ERROR)
		printf("Error: Invalid argument\n");
	else if (err == MALLOC_ERROR)
		printf("Error: Malloc failed\n");
	else if (err == THREAD_ERROR)
		printf("Error: Thread failed\n");
	else if (err == MUTEX_ERROR)
		printf("Error: Mutex failed\n");
	ft_free_data(data);
	exit(-1);
	return (-1);
}

int	ft_init(t_data *data)
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->nb_philo + 1, sizeof(t_philo));
	if (!data->philo)
		return (MALLOC_ERROR);
	gettimeofday(&data->start, NULL);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].state = THINKING;
		data->philo[i].last_meal.tv_sec = data->start.tv_sec;
		data->philo[i].last_meal.tv_usec = data->start.tv_usec;
		i++;
	}
	data->fork = ft_calloc(data->nb_philo + 1, sizeof(t_fork));
	if (!data->fork)
		return (MALLOC_ERROR);
	i = 0;
	while (i < data->nb_philo)
	{
		data->fork[i].id = i;
		data->fork[i].used = FALSE;
		i++;
	}
	return (0);
}

void	*ft_philo(void *arg)
{
	t_data *data;
	int		id;
	t_philo	*philo;
	t_fork	*fork_left;
	t_fork	*fork_right;
	
	data = ((t_args *) arg)->data;
	id = ((t_args *) arg)->id;
	free(arg);
	ft_print_action(data, id, JOIN);
	philo = &data->philo[id];
	while (!data->simulating)
		;
	while (data->simulating)
	{
		if (philo->state == THINKING)
		{
			if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
			{
				ft_print_action(data, id, GET_FULL);
				philo->state = FULL;
				break ;
			}
			ft_print_action(data, id, THINK);
			fork_left = &data->fork[id];
			fork_right = &data->fork[(id + 1) % data->nb_philo];
			if (id % 2)
			{
				pthread_mutex_lock(&fork_left->mutex);
				fork_left->used = TRUE;
				ft_print_action(data, id, TAKE_LEFT_FORK);
				pthread_mutex_lock(&fork_right->mutex);
				fork_right->used = TRUE;
				ft_print_action(data, id, TAKE_RIGHT_FORK);
			}
			else
			{
				pthread_mutex_lock(&fork_right->mutex);
				fork_right->used = TRUE;
				ft_print_action(data, id, TAKE_RIGHT_FORK);
				pthread_mutex_lock(&fork_left->mutex);
				fork_left->used = TRUE;
				ft_print_action(data, id, TAKE_LEFT_FORK);
			}
			philo->state = EATING;
			ft_print_action(data, id, EAT);
			philo->last_meal = (struct timeval){ft_get_time(data), 0};
		}
		else if (philo->state == EATING)
		{
			if (ft_get_time(data) - philo->last_meal.tv_sec > data->time_to_eat)
			{
				philo->nb_meal++;
				philo->last_meal = (struct timeval){ft_get_time(data), 0};
				pthread_mutex_unlock(&fork_left->mutex);
				fork_left->used = FALSE;
				ft_print_action(data, id, RELEASE_LEFT_FORK);
				pthread_mutex_unlock(&fork_right->mutex);
				fork_right->used = FALSE;
				ft_print_action(data, id, RELEASE_RIGHT_FORK);
				philo->state = SLEEPING;
				ft_print_action(data, id, SLEEP);
			}
		}
		else if (philo->state == SLEEPING)
		{
			if (ft_get_time(data) - philo->last_meal.tv_sec > data->time_to_sleep)
			{
				philo->state = THINKING;
			}
		}
		usleep(USLEEP);
	}
	return (NULL);
}

int	ft_start(t_data *data)
{
	int	i;
	t_args	*arg;

	data->simulating = FALSE;
	i = 0;
	while (i < data->nb_philo)
	{
		arg = ft_calloc(1, sizeof(t_args));
		if (!arg)
			return (MALLOC_ERROR);
		arg->data = data;
		arg->id = i;
		if (pthread_create(&data->philo[i].thread, NULL, &ft_philo, arg))
			return (THREAD_ERROR);
		i++;
	}
	ft_print_broadcast(data, "Simulation started");
	data->simulating = TRUE;
	return (0);
}

void	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo[i].thread)
			pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	main(/*int ac, char **av*/)
{
	t_data	data;
	t_error	err;

	int ac = 5;
	char *av[7] = {NULL};
	av[1] = "4";
	av[2] = "3000";
	av[3] = "1000";
	av[4] = "1000";
	av[5] = "5";
	if (ac < 5 || ac > 6)
		return (ft_error(ARGC_ERROR, &data));
	err = ft_parse(&data, ac - 1, av + 1) || ft_init(&data) || ft_start(&data);
	if (err != NONE)
		return (ft_error(err, &data));
	while (data.simulating)
	{
		int i = 0;
		t_bool all_full = TRUE;
		while (i < data.nb_philo)
		{
			if (data.philo[i].state != FULL)
				all_full = FALSE;
			if (ft_get_time(&data) - data.philo[i].last_meal.tv_sec > data.time_to_die
				&& data.philo[i].state != EATING && data.philo[i].state != FULL)
			{
				ft_print_action(&data, i, DIE);
				data.simulating = FALSE;
				break ;
			}
			usleep(USLEEP);
			i++;
		}
		if (all_full)
		{
			ft_print_broadcast(&data, "All philosophers are full");
			data.simulating = FALSE;
		}
	}
	int i = 0;
	while (i < data.nb_philo)
	{
		pthread_detach(data.philo[i].thread);
		i++;
	}
	ft_print_broadcast(&data, "Simulation ended");
	return (ft_error(NONE, &data));
}
