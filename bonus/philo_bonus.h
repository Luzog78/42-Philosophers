/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:18 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/14 14:28:12 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include "../core/philo.h"
# include <semaphore.h>

typedef struct s_data
{
	int				nb_philo;
	t_ll			time_to_die;
	t_ll			time_to_eat;
	t_ll			time_to_sleep;
	int				nb_meal;
	sem_t			forks_sem;
	t_philo			*philo;
	pthread_mutex_t	print_mutex;
	t_ll			start;
	t_sim_state		state;
	int				pid;
}	t_data;

#endif
