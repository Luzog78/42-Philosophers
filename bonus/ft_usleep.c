/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:12:01 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 16:13:04 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_ll	ft_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000000 + current.tv_usec);
}

void	ft_usleep(t_ll time)
{
	t_ll	start;

	start = ft_time();
	while (ft_time() - start < time)
		usleep(30);
}
