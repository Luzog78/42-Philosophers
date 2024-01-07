/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:45:22 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/07 07:17:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

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
		data->fork[i].id = i;
		pthread_mutex_init(&data->philo[i].mutex, NULL);
		pthread_mutex_init(&data->fork[i].mutex, NULL);
		pthread_mutex_init(&data->fork[i].var_mutex, NULL);
		ft_set_philo_state(&data->philo[i], THINKING);
		ft_reset_last_meal(data, &data->philo[i]);
		ft_set_fork_use(&data->fork[i], 0, TRUE);
		i++;
	}
	return (0);
}
