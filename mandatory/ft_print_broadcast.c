/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_broadcast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:39 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 05:28:54 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_print_broadcast(t_data *data, char *str)
{
	pthread_mutex_lock(&data->print_mutex);
	ft_print_timestamp(data);
	printf(">> %s <<\n", str);
	pthread_mutex_unlock(&data->print_mutex);
}
