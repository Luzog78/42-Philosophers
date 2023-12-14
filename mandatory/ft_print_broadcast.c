/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_broadcast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:39 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 17:15:21 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_print_broadcast(t_data *data, char *str, t_ui timestamp)
{
	pthread_mutex_lock(&data->print_list_mutex);
	ft_print_timestamp(timestamp);
	printf(">> %s <<\n", str);
	pthread_mutex_unlock(&data->print_list_mutex);
}
