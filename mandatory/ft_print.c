/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:13:08 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 16:29:14 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	*ft_print(void *arg)
{
	t_data			*data;

	data = (t_data *) arg;
	while (1)
	{
		if (data->print_list != NULL)
		{
			pthread_mutex_lock(&data->print_list_mutex);
			ft_print_action(data, data->print_list);
			if (data->print_list->action == DIE)
			{
				ft_free_print_list(&data->print_list);
				pthread_mutex_unlock(&data->print_list_mutex);
				return (NULL);
			}
			ft_pop_print_list(&data->print_list);
			pthread_mutex_unlock(&data->print_list_mutex);
		}
		ft_usleep(10);
	}
	return (NULL);
}
