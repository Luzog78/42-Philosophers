/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:47:32 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/05 06:47:44 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_action(t_data *data, int id, t_action action)
{
	pthread_mutex_lock(&data->print_mutex);
	ft_print_timestamp(data);
	printf("Philosopher %d ", id);
	if (action == JOIN)
		printf("is joining the table");
	else if (action == THINK)
		printf("is thinking");
	else if (action == TAKE_LEFT_FORK)
		printf("has taken his left fork");
	else if (action == TAKE_RIGHT_FORK)
		printf("has taken his right fork");
	else if (action == EAT)
		printf("is eating  (%d%s meal)", data->philo[id].nb_meal + 1, ft_print_get_nth(data->philo[id].nb_meal + 1));
	else if (action == RELEASE_LEFT_FORK)
		printf("has released his left fork");
	else if (action == RELEASE_RIGHT_FORK)
		printf("has released his right fork");
	else if (action == SLEEP)
		printf("is sleeping");
	else if (action == GET_FULL)
		printf("is full");
	else if (action == DIE)
		printf("died");
	printf("\n");
	pthread_mutex_unlock(&data->print_mutex);
}
