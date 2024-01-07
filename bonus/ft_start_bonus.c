/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:44:29 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 13:40:51 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_start(t_data *data)
{
	int		i;
	t_args	*arg;

	ft_set_data_state(data, PENDING);
	i = 0;
	while (i < data->nb_philo)
	{
		arg = ft_calloc(1, sizeof(t_args));
		if (!arg)
			return (MALLOC_ERROR);
		arg->data = data;
		arg->id = i;
		data->pid = fork();
		if (data->pid == -1)
			return (PROCESS_ERROR);
		if (data->pid == 0)
		{
			ft_philo(arg);
			return (PROCESS_END);
		}
		ft_print_action(data, i, JOIN);
		i++;
	}
	ft_print_broadcast(data, "Simulation started");
	data->start = ft_get_time(NULL);
	ft_set_data_state(data, RUNNING);
	return (0);
}
