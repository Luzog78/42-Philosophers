/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:47:32 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 05:26:52 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print_action(t_data *data, int id, t_action action)
{
	pthread_mutex_lock(&data->print_mutex);
	ft_print_timestamp(data);
	printf("Philosopher %d ", id + 1);
	if (action == JOIN)
		printf("is joining the table\n");
	else if (action == THINK)
		printf("is thinking\n");
	else if (action == TAKE_LEFT_FORK)
		printf("has taken his left fork\n");
	else if (action == TAKE_RIGHT_FORK)
		printf("has taken his right fork\n");
	else if (action == EAT)
		printf("is eating  (%d%s meal)\n", data->philo[id].nb_meal + 1,
			ft_print_get_nth(data->philo[id].nb_meal + 1));
	else if (action == RELEASE_LEFT_FORK)
		printf("has released his left fork\n");
	else if (action == RELEASE_RIGHT_FORK)
		printf("has released his right fork\n");
	else if (action == SLEEP)
		printf("is sleeping\n");
	else if (action == GET_FULL)
		printf("is full\n");
	else if (action == DIE)
		printf("died\n");
	pthread_mutex_unlock(&data->print_mutex);
}
