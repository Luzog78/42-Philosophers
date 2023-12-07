/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_last_meal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 03:35:07 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 03:35:43 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_reset_last_meal(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = ft_get_time(data);
	pthread_mutex_unlock(&philo->mutex);
}
