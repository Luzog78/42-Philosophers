/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:48:02 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/06 15:35:20 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	pthread_mutex_destroy(&data->print_mutex);
	if (data->philo)
		free(data->philo);
	i = 0;
	if (data->fork)
	{
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->fork[i].mutex);
			i++;
		}
		free(data->fork);
	}
}