/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mandatory.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:18 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/17 13:28:41 by ysabik           ###   ########.fr       */
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
	t_ll			time_to_die;
	t_ll			time_to_eat;
	t_ll			time_to_sleep;
	int				nb_meal;
	t_fork			*fork;
	t_philo			*philo;
	t_ll			start;
	t_sim_state		state;
	pthread_mutex_t	print_mutex;
}	t_data;

#endif
