/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 14:12:18 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_think(t_data *data, int id, t_philo *philo);
void	ft_eat(t_data *data, int id, t_philo *philo);
void	ft_sleep(t_data *data, t_philo *philo);

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
	while (data->state == RUNNING && philo->state != FULL)
	{
		if (philo->state == THINKING)
			ft_think(data, id, philo);
		else if (philo->state == EATING)
			ft_eat(data, id, philo);
		else if (philo->state == SLEEPING)
			ft_sleep(data, philo);
		//ft_usleep(USLEEP);
	}
	return (NULL);
}

void	ft_think(t_data *data, int id, t_philo *philo)
{
	if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
	{
		ft_print_action(data, id, GET_FULL);
		philo->state = FULL;
		return ;
	}
	ft_print_action(data, id, THINK);
	if (id % 2 == 0 && ft_get_time(data) < 1000)
		ft_usleep(1000);
	sem_wait(&data->forks_sem);
	ft_print_action(data, id, TAKE_LEFT_FORK);
	if (data->nb_philo == 1)
		ft_usleep(data->time_to_die * 10 + 10000000);
	sem_wait(&data->forks_sem);
	ft_print_action(data, id, TAKE_RIGHT_FORK);
	philo->state = EATING;
	ft_print_action(data, id, EAT);
	ft_reset_last_meal(data, philo);
}

void	ft_eat(t_data *data, int id, t_philo *philo)
{
	if (ft_get_time(data) - philo->last_meal > data->time_to_eat)
	{
		philo->nb_meal++;
		sem_post(&data->forks_sem);
		ft_print_action(data, id, RELEASE_LEFT_FORK);
		sem_post(&data->forks_sem);
		ft_print_action(data, id, RELEASE_RIGHT_FORK);
		philo->state = SLEEPING;
		ft_print_action(data, id, SLEEP);
	}
}

void	ft_sleep(t_data *data, t_philo *philo)
{
	if (ft_get_time(data) - philo->last_meal > data->time_to_sleep)
	{
		ft_usleep(data->time_to_eat);
		philo->state = THINKING;
	}
}
