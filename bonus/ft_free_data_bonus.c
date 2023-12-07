/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:48:02 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 05:04:50 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	sem_close(&data->forks_sem);
	pthread_mutex_destroy(&data->print_mutex);
	i = 0;
	if (data->philo)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->philo[i].mutex);
			i++;
		}
		free(data->philo);
	}
}
