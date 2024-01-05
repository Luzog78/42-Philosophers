/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_philo_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:17:32 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 14:18:11 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

t_state	ft_get_philo_state(t_philo *philo)
{
	t_state	state;

	pthread_mutex_lock(&philo->mutex);
	state = philo->state;
	pthread_mutex_unlock(&philo->mutex);
	return (state);
}
