/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:47:32 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 15:21:03 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_print_action(t_data *data, t_print_list *print)
{
	ft_print_timestamp(print->timestamp);
	printf("Philosopher %d ", print->id + 1);
	if (print->action == JOIN)
		printf("is joining the table\n");
	else if (print->action == THINK)
		printf("is thinking\n");
	else if (print->action == TAKE_LEFT_FORK)
		printf("has taken his left fork\n");
	else if (print->action == TAKE_RIGHT_FORK)
		printf("has taken his right fork\n");
	else if (print->action == EAT)
		printf("is eating  (%d%s meal)\n", data->philo[print->id].nb_meal + 1,
			ft_print_get_nth(data->philo[print->id].nb_meal + 1));
	else if (print->action == RELEASE_LEFT_FORK)
		printf("has released his left fork\n");
	else if (print->action == RELEASE_RIGHT_FORK)
		printf("has released his right fork\n");
	else if (print->action == SLEEP)
		printf("is sleeping\n");
	else if (print->action == GET_FULL)
		printf("is full\n");
	else if (print->action == DIE)
		printf("died\n");
}
