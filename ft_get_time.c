/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:05 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/05 06:46:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @returns	The time in milliseconds since the start of the simulation.
*/
int	ft_get_time(t_data *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec - data->start.tv_sec) * 1000
		+ (current.tv_usec - data->start.tv_usec) / 1000);
}
