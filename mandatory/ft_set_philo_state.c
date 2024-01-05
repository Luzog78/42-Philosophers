/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_philo_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 06:40:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 13:45:45 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_set_philo_state(t_philo *philo, t_state state)
{
	pthread_mutex_lock(&philo->mutex);
	philo->state = state;
	pthread_mutex_unlock(&philo->mutex);
}
