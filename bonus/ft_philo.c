/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:54 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 17:07:10 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_think(t_data *data, int id, t_philo *philo);
static void	ft_eat(t_data *data, int id, t_philo *philo);
static void	ft_sleep(t_data *data, t_philo *philo);

void ft_wait(char *name)
{
	sem_t	*sem;

	sem = sem_open(name, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	sem_wait(sem);
	sem_close(sem);
}

void ft_post(char *name)
{
	sem_t	*sem;

	sem = sem_open(name, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	sem_post(sem);
	sem_close(sem);
}

void	*ft_death_checker(void *arg)
{
	t_data	*data;
	
	data = (t_data *) arg;
	if (ft_get_time(data) - data->philo.last_meal >= data->time_to_die)
	{
		ft_print_action(data, data->philo.id, DIE);
		ft_post(DIES_SEM);
	}
	return (NULL);
}

void	ft_philo(t_data *data)
{
	int		id;
	t_philo	*philo;

	philo = &data->philo;
	id = philo->id;
	ft_wait(START_SEM);
	if (pthread_create(&philo->death_thread, NULL, ft_death_checker, data) != 0)
		return ;
	if (id % 2 == 0)
		ft_usleep(2000);
	philo->state = THINKING;
	while (philo->state != FULL)
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
}

static void	ft_think(t_data *data, int id, t_philo *philo)
{
	if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
	{
		ft_print_action(data, id, GET_FULL);
		philo->state = FULL;
		return ;
	}
	ft_print_action(data, id, THINK);
	ft_wait(FORKS_SEM);
	ft_print_action(data, id, TAKE_LEFT_FORK);
	if (data->nb_philo == 1)
		ft_usleep(data->time_to_die + 100);
	ft_wait(FORKS_SEM);
	ft_print_action(data, id, TAKE_RIGHT_FORK);
	philo->state = EATING;
	ft_print_action(data, id, EAT);
	philo->last_meal = ft_get_time(data);
}

static void	ft_eat(t_data *data, int id, t_philo *philo)
{
	if (ft_get_time(data) - philo->last_meal >= data->time_to_eat)
	{
		philo->nb_meal++;
		ft_post(FORKS_SEM);
		ft_print_action(data, id, RELEASE_LEFT_FORK);
		ft_post(FORKS_SEM);
		ft_print_action(data, id, RELEASE_RIGHT_FORK);
		if (data->nb_meal != -1 && philo->nb_meal >= data->nb_meal)
		{
			ft_print_action(data, id, GET_FULL);
			philo->state = FULL;
			ft_post(FULLS_SEM);
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
