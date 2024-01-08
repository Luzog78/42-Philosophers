/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:29 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 16:55:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	ft_post(t_data *data);
static void	ft_init_philo(t_data *data, int id);

int	ft_start(t_data *data)
{
	int		i;
	int		pid;

	data->state = PENDING;
	data->start = ft_get_time(NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			ft_init_philo(data, i);
			data->is_main_process = FALSE;
			return (0);
		}
		data->philo_pids[i] = pid;
		ft_print_action(data, i, JOIN);
		i++;
	}
	ft_print_broadcast(data, "Simulation started");
	data->state = RUNNING;
	ft_post(data);
	return (0);
}

void	ft_post(t_data *data)
{
	sem_t	*sem;
	int		i;

	sem = sem_open(START_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		sem_post(sem);
		i++;
	}
	sem_close(sem);
}

void	ft_init_philo(t_data *data, int id)
{
	t_philo	*philo;

	philo = &data->philo;
	philo->id = id;
	philo->last_meal = ft_get_time(NULL);
	philo->nb_meal = 0;
	philo->state = THINKING;
}
