/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_broadcast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:39 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/07 07:40:15 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_broadcast(t_data *data, char *str)
{
	pthread_mutex_lock(&data->print_mutex);
	ft_print_timestamp(ft_get_time(data));
	printf(">> %s <<\n", str);
	pthread_mutex_unlock(&data->print_mutex);
}
