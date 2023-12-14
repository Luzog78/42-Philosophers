/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 17:16:31 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_think(t_data *data, int id, t_philo *philo);
void	ft_eat(t_data *data, int id, t_philo *philo);
void	ft_sleep(t_data *data, int id, t_philo *philo);

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
	philo->last_meal += 2000;
	while (data->state == RUNNING && philo->state != FULL)
	{
		ft_think(data, id, philo);
		if (philo->state == FULL)
			break ;
		ft_eat(data, id, philo);
		ft_sleep(data, id, philo);
	}
	return (NULL);
}

void	ft_think(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
	{
		philo->state = FULL;
		ft_add_print_list(data, id, GET_FULL, ft_get_time(data));
		return ;
	}
	philo->state = THINKING;
	ft_add_print_list(data, id, THINK, ft_get_time(data));
	fork_left = &data->fork[id];
	fork_right = &data->fork[(id + 1) % data->nb_philo];
	pthread_mutex_lock(&fork_left->mutex);
	fork_left->used = TRUE;
	ft_add_print_list(data, id, TAKE_LEFT_FORK, ft_get_time(data));
	if (data->nb_philo == 1)
		ft_usleep(data->time_to_die * 10 + 10000000);
	pthread_mutex_lock(&fork_right->mutex);
	fork_right->used = TRUE;
	ft_add_print_list(data, id, TAKE_RIGHT_FORK, ft_get_time(data));
}

void	ft_eat(t_data *data, int id, t_philo *philo)
{
	t_fork	*fork_left;
	t_fork	*fork_right;

	philo->state = EATING;
	ft_add_print_list(data, id, EAT, ft_get_time(data));
	ft_reset_last_meal(data, philo);
	ft_usleep(data->time_to_eat);
	fork_left = &data->fork[id];
	fork_right = &data->fork[(id + 1) % data->nb_philo];
	philo->nb_meal++;
	pthread_mutex_unlock(&fork_left->mutex);
	fork_left->used = FALSE;
	ft_add_print_list(data, id, RELEASE_LEFT_FORK, ft_get_time(data));
	pthread_mutex_unlock(&fork_right->mutex);
	fork_right->used = FALSE;
	ft_add_print_list(data, id, RELEASE_RIGHT_FORK, ft_get_time(data));
}

void	ft_sleep(t_data *data, int id, t_philo *philo)
{
	philo->state = SLEEPING;
	ft_add_print_list(data, id, SLEEP, ft_get_time(data));
	ft_usleep(data->time_to_sleep + data->time_to_eat);
}
