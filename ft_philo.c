/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/05 07:37:29 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (data->state == RUNNING)
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
				//philo->last_meal = (struct timeval){ft_get_time(data), 0};
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
