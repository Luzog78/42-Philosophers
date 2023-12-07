/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_simulation_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:45:22 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 05:53:22 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_init_simulation(t_data *data)
{
	int	i;

	i = 0;
	sem_init(&data->forks_sem, 1, data->nb_philo);
	data->philo = ft_calloc(data->nb_philo + 1, sizeof(t_philo));
	if (!data->philo)
		return (MALLOC_ERROR);
	data->start = ft_get_time(NULL);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].state = THINKING;
		data->philo[i].last_meal = 0;
		pthread_mutex_init(&data->philo[i].mutex, NULL);
		i++;
	}
	return (0);
}
