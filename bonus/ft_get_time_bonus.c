/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:05 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/14 14:28:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @returns	The time in microseconds since the start of the simulation.
*/
t_ll	ft_get_time(t_data *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (!data)
		return (current.tv_sec * 1000000 + current.tv_usec);
	return (current.tv_sec * 1000000 + current.tv_usec - data->start);
}
