/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:45:22 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/06 23:31:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_simulation(t_data *data)
{
	int	i;

	i = 0;
	data->philo = ft_calloc(data->nb_philo + 1, sizeof(t_philo));
	data->fork = ft_calloc(data->nb_philo + 1, sizeof(t_fork));
	if (!data->philo || !data->fork)
		return (MALLOC_ERROR);
	data->start = ft_get_time(NULL);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i;
		data->philo[i].state = THINKING;
		data->philo[i].last_meal = 0;
		data->fork[i].id = i;
		data->fork[i].used = FALSE;
		pthread_mutex_init(&data->fork[i].mutex, NULL);
		i++;
	}
	return (0);
}
