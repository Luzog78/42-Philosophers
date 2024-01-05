/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_data_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:17:32 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 14:17:50 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

t_sim_state	ft_get_data_state(t_data *data)
{
	t_sim_state	state;

	pthread_mutex_lock(&data->state_mutex);
	state = data->state;
	pthread_mutex_unlock(&data->state_mutex);
	return (state);
}
