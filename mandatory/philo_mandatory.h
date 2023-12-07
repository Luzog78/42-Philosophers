/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:18 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 05:33:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_MANDATORY_H
# define PHILO_MANDATORY_H

# include "../core/philo.h"

typedef struct s_fork
{
	int				id;
	t_bool			used;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_data
{
	int				nb_philo;
	t_ui			time_to_die;
	t_ui			time_to_eat;
	t_ui			time_to_sleep;
	int				nb_meal;
	t_fork			*fork;
	t_philo			*philo;
	pthread_mutex_t	print_mutex;
	t_ui			start;
	t_sim_state		state;
}	t_data;

#endif
