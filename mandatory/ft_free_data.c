/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:48:02 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/16 16:14:41 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	pthread_mutex_destroy(&data->print_list_mutex);
	i = 0;
	if (data->philo || data->fork)
	{
		while (i < data->nb_philo)
		{
			if (data->philo)
				pthread_mutex_destroy(&data->philo[i].mutex);
			if (data->fork)
				pthread_mutex_destroy(&data->fork[i].mutex);
			i++;
		}
		if (data->philo)
			free(data->philo);
		if (data->fork)
			free(data->fork);
	}
}
