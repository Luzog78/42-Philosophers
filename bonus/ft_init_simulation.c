/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_simulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:45:22 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 17:06:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_sem(char *name, int value);

int	ft_init_simulation(t_data *data)
{
	data->philo_pids = ft_calloc(data->nb_philo + 1, sizeof(t_philo));
	if (!data->philo_pids)
		return (MALLOC_ERROR);
	if (!init_sem(FORKS_SEM, data->nb_philo) || !init_sem(PRINT_SEM, 1)
		|| !init_sem(FULLS_SEM, 0) || !init_sem(DIES_SEM, 0) || !init_sem(START_SEM, 0))
		return (SEMAPHORE_ERROR);
	return (0);
}

static t_bool	init_sem(char *name, int value)
{
	sem_t	*sem;

	unlink(name);
	sem = sem_open(name, O_CREAT, 0777, 0);
	if (sem == SEM_FAILED)
		return (FALSE);
	while (value)
	{
		sem_post(sem);
		value--;
	}
	sem_close(sem);
	return (TRUE);
}
