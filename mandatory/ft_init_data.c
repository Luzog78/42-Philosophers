/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:26:09 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 06:45:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_init_data(t_data *data)
{
	data->philo = NULL;
	data->fork = NULL;
	data->nb_philo = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	pthread_mutex_init(&data->state_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}
