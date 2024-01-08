/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_broadcast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:39 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 17:29:21 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_broadcast(t_data *data, char *str)
{
	sem_t	*sem;

	sem = sem_open(PRINT_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	sem_wait(sem);
	if (data->can_print)
	{
		ft_print_timestamp(ft_get_time(data));
		printf(">> %s <<\n", str);
	}
	sem_post(sem);
	sem_close(sem);
}
