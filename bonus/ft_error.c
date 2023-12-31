/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:45:39 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 16:10:13 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_error err, t_data *data)
{
	if (err == ARGC_ERROR)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo <%s> <%s> <%s> <%s> [<%s>]\n",
			"number_of_philosophers", "time_to_die", "time_to_eat",
			"time_to_sleep", "number_of_meals");
	}
	else if (err == ARG_ERROR)
		printf("Error: Invalid argument\n");
	else if (err == MALLOC_ERROR)
		printf("Error: Malloc failed\n");
	else if (err == THREAD_ERROR)
		printf("Error: Thread failed\n");
	else if (err == PROCESS_ERROR)
		printf("Error: Fork failed\n");
	else if (err == MUTEX_ERROR)
		printf("Error: Mutex failed\n");
	else if (err == SEMAPHORE_ERROR)
		printf("Error: Semaphore failed\n");
	ft_free_data(data);
	return (-1);
}
