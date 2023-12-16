/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:47:32 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/16 16:42:01 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

static t_bool	ft_mask(t_action action)
{
	return (action != JOIN
		&& action != RELEASE_LEFT_FORK
		&& action != RELEASE_RIGHT_FORK);
}

static void	ft_switch(t_data *data, int id, t_action action)
{
	if (action == THINK)
		printf("is thinking");
	else if (action == TAKE_LEFT_FORK || action == TAKE_RIGHT_FORK)
		printf("has taken a fork");
	else if (action == EAT)
		printf("is eating (%d%s meal)", data->philo[id].nb_meal + 1,
			ft_print_get_nth(data->philo[id].nb_meal + 1));
	else if (action == SLEEP)
		printf("is sleeping");
	else if (action == GET_FULL)
		printf("is full");
	else if (action == DIE)
		printf("died");
}

void	ft_print_action(t_data *data, int id, t_action action)
{
	if (!ft_mask(action))
		return ;
	pthread_mutex_lock(&data->print_list_mutex);
	if (data->state == RUNNING)
	{
		ft_print_timestamp(ft_get_time(data));
		printf("%3d  ", id + 1);
		ft_switch(data, id, action);
		printf("\n");
	}
	pthread_mutex_unlock(&data->print_list_mutex);
}
