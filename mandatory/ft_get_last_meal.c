/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_meal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:17:33 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/07 07:40:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ll	ft_get_last_meal(t_philo *philo)
{
	t_ll	last_meal;

	pthread_mutex_lock(&philo->mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->mutex);
	return (last_meal);
}
