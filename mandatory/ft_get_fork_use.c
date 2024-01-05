/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_fork_used.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:24:25 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 17:08:17 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

int	ft_get_fork_use(t_fork *fork)
{
	int	use;

	pthread_mutex_lock(&fork->var_mutex);
	if (fork->used_by_left)
		use = 1;
	else if (fork->used_by_right)
		use = 2;
	else
		use = 0;
	pthread_mutex_unlock(&fork->var_mutex);
	return (use);
}
