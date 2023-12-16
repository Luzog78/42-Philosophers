/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:29 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/16 15:36:59 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

int	ft_start(t_data *data)
{
	int		i;
	t_args	*arg;

	data->state = PENDING;
	i = 0;
	while (i < data->nb_philo)
	{
		arg = ft_calloc(1, sizeof(t_args));
		if (!arg)
			return (MALLOC_ERROR);
		arg->data = data;
		arg->id = i;
		if (pthread_create(&data->philo[i].thread, NULL, &ft_philo, arg))
			return (THREAD_ERROR);
		ft_print_action(data, i, JOIN);
		i++;
	}
	ft_print_broadcast(data, "Simulation started", ft_get_time(data));
	data->start = ft_get_time(NULL);
	data->state = RUNNING;
	return (0);
}
