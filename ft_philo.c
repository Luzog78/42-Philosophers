/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 03:36:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_think(t_data *data, int id, t_philo *philo);
void	ft_eat(t_data *data, int id, t_philo *philo);
void	ft_sleep(t_data *data, int id, t_philo *philo);

void	*ft_philo(void *arg)
{
	t_data	*data;
	int		id;
	t_philo	*philo;
	t_fork	*fork_left;
	t_fork	*fork_right;

	data = ((t_args *) arg)->data;
	id = ((t_args *) arg)->id;
	free(arg);
	philo = &data->philo[id];
	while (data->state == PENDING)
		;
	while (data->state == RUNNING && philo->state != FULL)
	{
		if (philo->state == THINKING)
			ft_think(data, id, philo);
		else if (philo->state == EATING)
			ft_eat(data, id, philo);
		else if (philo->state == SLEEPING)
			ft_sleep(data, id, philo);
		ft_usleep(USLEEP);
	}
	return (NULL);
}

void	ft_think(t_data *data, int id, t_philo *philo)
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
	if (id % 2 == 0)
		ft_usleep(1000);
	pthread_mutex_lock(&fork_left->mutex);
	fork_left->used = TRUE;
	ft_print_action(data, id, TAKE_LEFT_FORK);
	if (data->nb_philo == 1)
		ft_usleep(data->time_to_die * 10 + 10000000);
	pthread_mutex_lock(&fork_right->mutex);
	fork_right->used = TRUE;
	ft_print_action(data, id, TAKE_RIGHT_FORK);
	philo->state = EATING;
	ft_print_action(data, id, EAT);
	ft_reset_last_meal(data, philo);
}

void	ft_eat(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	if (ft_get_time(data) - philo->last_meal > data->time_to_eat)
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
		philo->state = SLEEPING;
		ft_print_action(data, id, SLEEP);
	}
}

void	ft_sleep(t_data *data, int id, t_philo *philo)
{
	if (ft_get_time(data) - philo->last_meal > data->time_to_sleep)
	{
		ft_usleep(data->time_to_eat);
		philo->state = THINKING;
	}
}
