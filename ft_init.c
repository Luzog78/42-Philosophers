/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:45:22 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/06 18:27:57 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		data->philo[i].last_meal.tv_sec = 0;
		data->philo[i].last_meal.tv_usec = 0;
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
		pthread_mutex_init(&data->fork[i].mutex, NULL);
		i++;
	}
	return (0);
}