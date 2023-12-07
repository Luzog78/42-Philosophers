/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:05 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 05:28:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

/**
 * @returns	The time in microseconds since the start of the simulation.
*/
t_ui	ft_get_time(t_data *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (!data)
		return (current.tv_sec * 1000000 + current.tv_usec);
	return (current.tv_sec * 1000000 + current.tv_usec - data->start);
}
