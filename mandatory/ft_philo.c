/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/07 07:29:23 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

static void	ft_think(t_data *data, int id, t_philo *philo);
static void	ft_eat(t_data *data, int id, t_philo *philo);
static void	ft_sleep(t_data *data, t_philo *philo);
static void	*ft_clear_philo(t_data *data, int id);

void	*ft_philo(void *arg)
{
	t_data	*data;
	int		id;
	t_philo	*philo;

	data = ((t_args *) arg)->data;
	id = ((t_args *) arg)->id;
	free(arg);
	philo = &data->philo[id];
	while (ft_get_data_state(data) == PENDING)
		usleep(USLEEP);
	if (id % 2 == 0)
		ft_usleep(2000);
	while (ft_get_data_state(data) == RUNNING
		&& ft_get_philo_state(philo) != FULL)
	{
		if (ft_get_philo_state(philo) == THINKING)
			ft_think(data, id, philo);
		if (ft_get_philo_state(philo) == EATING)
			ft_eat(data, id, philo);
		if (ft_get_philo_state(philo) == SLEEPING)
			ft_sleep(data, philo);
		if (ft_get_philo_state(philo) != FULL)
			ft_usleep(USLEEP);
	}
	return (ft_clear_philo(data, id));
}

static void	*ft_clear_philo(t_data *data, int id)
{
	pthread_mutex_lock(&data->fork[id].var_mutex);
	if (ft_get_fork_use(&data->fork[id], FALSE) == 2)
	{
		pthread_mutex_unlock(&data->fork[id].mutex);
		ft_set_fork_use(&data->fork[id], 0, FALSE);
	}
	pthread_mutex_unlock(&data->fork[id].var_mutex);
	pthread_mutex_lock(&data->fork[(id + 1) % data->nb_philo].var_mutex);
	if (ft_get_fork_use(&data->fork[(id + 1) % data->nb_philo], FALSE) == 1)
	{
		pthread_mutex_unlock(&data->fork[(id + 1) % data->nb_philo].mutex);
		ft_set_fork_use(&data->fork[(id + 1) % data->nb_philo], 0, FALSE);
	}
	pthread_mutex_unlock(&data->fork[(id + 1) % data->nb_philo].var_mutex);
	return (NULL);
}

static void	ft_think(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
	{
		ft_print_action(data, id, GET_FULL);
		ft_set_philo_state(philo, FULL);
		return ;
	}
	ft_print_action(data, id, THINK);
	fork_left = &data->fork[id];
	fork_right = &data->fork[(id + 1) % data->nb_philo];
	pthread_mutex_lock(&fork_left->mutex);
	ft_set_fork_use(fork_left, 2, TRUE);
	ft_print_action(data, id, TAKE_LEFT_FORK);
	if (data->nb_philo == 1)
		ft_usleep(data->time_to_die + 100);
	pthread_mutex_lock(&fork_right->mutex);
	ft_set_fork_use(fork_right, 1, TRUE);
	ft_print_action(data, id, TAKE_RIGHT_FORK);
	ft_set_philo_state(philo, EATING);
	ft_print_action(data, id, EAT);
	ft_reset_last_meal(data, philo);
}

static void	ft_eat(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	if (ft_get_time(data) - ft_get_last_meal(philo) >= data->time_to_eat)
	{
		fork_left = &data->fork[id];
		fork_right = &data->fork[(id + 1) % data->nb_philo];
		philo->nb_meal++;
		pthread_mutex_unlock(&fork_left->mutex);
		ft_set_fork_use(fork_left, 0, TRUE);
		ft_print_action(data, id, RELEASE_LEFT_FORK);
		pthread_mutex_unlock(&fork_right->mutex);
		ft_set_fork_use(fork_right, 0, TRUE);
		ft_print_action(data, id, RELEASE_RIGHT_FORK);
		if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
		{
			ft_print_action(data, id, GET_FULL);
			ft_set_philo_state(philo, FULL);
			return ;
		}
		ft_set_philo_state(philo, SLEEPING);
		ft_print_action(data, id, SLEEP);
	}
}

static void	ft_sleep(t_data *data, t_philo *philo)
{
	if (ft_get_time(data) - ft_get_last_meal(philo)
		>= data->time_to_sleep + data->time_to_eat)
		ft_set_philo_state(philo, THINKING);
}
