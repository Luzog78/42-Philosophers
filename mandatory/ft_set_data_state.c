/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_data_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 06:40:43 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 13:40:51 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_set_data_state(t_data *data, t_sim_state state)
{
	pthread_mutex_lock(&data->state_mutex);
	data->state = state;
	pthread_mutex_unlock(&data->state_mutex);
}
