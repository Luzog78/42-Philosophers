/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_print_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 15:09:43 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/09 17:14:27 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

void	ft_add_print_list(t_data *data, int id, t_action action, t_ui timestamp)
{
	t_print_list	*tmp;
	t_print_list	*last;

	pthread_mutex_lock(&data->print_list_mutex);
	tmp = ft_calloc(1, sizeof(t_print_list));
	tmp->id = id;
	tmp->action = action;
	tmp->timestamp = timestamp;
	tmp->next = NULL;
	if (!data->print_list)
	{
		data->print_list = tmp;
		pthread_mutex_unlock(&data->print_list_mutex);
		return ;
	}
	last = data->print_list;
	while (last->next)
		last = last->next;
	last->next = tmp;
	pthread_mutex_unlock(&data->print_list_mutex);
}
