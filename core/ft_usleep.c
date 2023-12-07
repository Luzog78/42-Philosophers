/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:12:01 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 03:48:40 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ui	ft_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000000 + current.tv_usec);
}

void	ft_usleep(t_ui time)
{
	t_ui	start;

	start = ft_time();
	while (ft_time() - start < time)
		usleep(30);
}
