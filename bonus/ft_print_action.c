/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:47:32 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 16:59:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ft_mask(t_action action)
{
	return (action != JOIN
		&& action != RELEASE_LEFT_FORK
		&& action != RELEASE_RIGHT_FORK
		&& action != GET_FULL);
}

static void	ft_switch(t_data *data, int id, t_action action)
{
	(void) id;
	if (action == JOIN)
		printf("is sitting around the table");
	else if (action == THINK)
		printf("is thinking");
	else if (action == TAKE_LEFT_FORK || action == TAKE_RIGHT_FORK)
		printf("has taken a fork");
	else if (action == RELEASE_LEFT_FORK || action == RELEASE_RIGHT_FORK)
		printf("has released a fork");
	else if (action == EAT)
		printf("is eating (%d%s meal)", data->philo.nb_meal + 1,
			ft_print_get_nth(data->philo.nb_meal + 1));
	else if (action == SLEEP)
		printf("is sleeping");
	else if (action == GET_FULL)
		printf("is full");
	else if (action == DIE)
		printf("died");
}

void	ft_print_action(t_data *data, int id, t_action action)
{
	sem_t	*sem;

	if (!ft_mask(action))
		return ;
	sem = sem_open(PRINT_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	sem_wait(sem);
	ft_print_timestamp(ft_get_time(data));
	printf("%3d  ", id + 1);
	ft_switch(data, id, action);
	printf("\n");
	sem_post(sem);
	sem_close(sem);
}
