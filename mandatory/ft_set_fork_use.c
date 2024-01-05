/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_fork_use.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:25:36 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 17:13:46 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"

/**
 * @param	use	0: not used, 1: used by left, 2: used by right
 */
void	ft_set_fork_use(t_fork *fork, int use)
{
	pthread_mutex_lock(&fork->var_mutex);
	if (use == 1)
	{
		fork->used_by_left = TRUE;
		fork->used_by_right = FALSE;
	}
	else if (use == 2)
	{
		fork->used_by_left = FALSE;
		fork->used_by_right = TRUE;
	}
	else
	{
		fork->used_by_left = FALSE;
		fork->used_by_right = FALSE;
	}
	pthread_mutex_unlock(&fork->var_mutex);
}
