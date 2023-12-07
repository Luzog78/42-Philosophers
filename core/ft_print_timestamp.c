/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_timestamp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 06:46:24 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/06 23:32:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_timestamp(t_data *data)
{
	int	ms;

	ms = ft_get_time(data) / 1000;
	printf("[%02d:%02d:%02d:%03d] ", ms / 3600000, ms / 60000 % 60,
		ms / 1000 % 60, ms % 1000);
	//printf("[%09d] ", ms);
}