/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 06:25:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

static void	ft_think(t_data *data, int id, t_philo *philo);
static void	ft_eat(t_data *data, int id, t_philo *philo);
static void	ft_sleep(t_data *data, t_philo *philo);

void	*ft_philo(void *arg)
{
	t_data	*data;
	int		id;
	t_philo	*philo;

	data = ((t_args *) arg)->data;
	id = ((t_args *) arg)->id;
	free(arg);
	philo = &data->philo[id];
	while (data->state == PENDING)
		;
	if (id % 2 == 0)
		ft_usleep(2000);
	philo->state = THINKING;
	while (data->state == RUNNING && philo->state != FULL)
	{
		if (philo->state == THINKING)
			ft_think(data, id, philo);
		if (philo->state == EATING)
			ft_eat(data, id, philo);
		if (philo->state == SLEEPING)
			ft_sleep(data, philo);
		if (philo->state != FULL)
			ft_usleep(USLEEP);
	}
	return (NULL);
}

static void	ft_think(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
	{
		ft_print_action(data, id, GET_FULL);
		philo->state = FULL;
		return ;
	}
	ft_print_action(data, id, THINK);
	fork_left = &data->fork[id];
	fork_right = &data->fork[(id + 1) % data->nb_philo];
	pthread_mutex_lock(&fork_left->mutex);
	fork_left->used = TRUE;
	ft_print_action(data, id, TAKE_LEFT_FORK);
	if (data->nb_philo == 1)
		ft_usleep(data->time_to_die + 1000);
	pthread_mutex_lock(&fork_right->mutex);
	fork_right->used = TRUE;
	ft_print_action(data, id, TAKE_RIGHT_FORK);
	philo->state = EATING;
	ft_print_action(data, id, EAT);
	ft_reset_last_meal(data, philo);
}

static void	ft_eat(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	if (ft_get_time(data) - philo->last_meal >= data->time_to_eat)
	{
		fork_left = &data->fork[id];
		fork_right = &data->fork[(id + 1) % data->nb_philo];
		philo->nb_meal++;
		pthread_mutex_unlock(&fork_left->mutex);
		fork_left->used = FALSE;
		ft_print_action(data, id, RELEASE_LEFT_FORK);
		pthread_mutex_unlock(&fork_right->mutex);
		fork_right->used = FALSE;
		ft_print_action(data, id, RELEASE_RIGHT_FORK);
		if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
		{
			ft_print_action(data, id, GET_FULL);
			philo->state = FULL;
			return ;
		}
		philo->state = SLEEPING;
		ft_print_action(data, id, SLEEP);
	}
}

static void	ft_sleep(t_data *data, t_philo *philo)
{
	if (ft_get_time(data) - philo->last_meal
		>= data->time_to_sleep + data->time_to_eat)
		philo->state = THINKING;
}
