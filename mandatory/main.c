/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:21 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/07 07:31:43 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_mandatory.h"
#include <stdio.h>

int	ft_init(int ac, char **av, t_data *data)
{
	t_error	err;

	ft_init_data(data);
	if (ac < 5 || ac > 6)
		return (ft_error(ARGC_ERROR, data));
	err = ft_parse(data, ac - 1, av + 1);
	if (err != NONE)
		return (ft_error(err, data));
	err = ft_init_simulation(data);
	if (err != NONE)
		return (ft_error(err, data));
	err = ft_start(data);
	if (err != NONE)
		return (ft_error(err, data));
	return (0);
}

t_bool	ft_main_thread(t_data *data, int i, t_bool all_full)
{
	while (i < data->nb_philo)
	{
		if (ft_get_philo_state(&data->philo[i]) != FULL)
			all_full = FALSE;
		if (ft_get_time(data) - ft_get_last_meal(&data->philo[i])
			> data->time_to_die && ft_get_philo_state(&data->philo[i]) != FULL)
		{
			ft_print_action(data, i, DIE);
			ft_set_data_state(data, ENDED);
			return (FALSE);
		}
		ft_usleep(USLEEP);
		i++;
	}
	if (all_full)
	{
		ft_set_data_state(data, ENDED);
		ft_print_broadcast(data, "All philosophers are full");
		return (FALSE);
	}
	return (TRUE);
}

// clear ; make re ; echo "" ;
// echo "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ; echo "" ;
// valgrind --tool=helgrind --track-lockorders=no --history-level=full -s --
// ./philo 100 700 200 200 2

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ft_init(ac, av, &data))
		return (1);
	while (ft_get_data_state(&data) == PENDING)
		;
	while (ft_get_data_state(&data) != ENDED)
	{
		if (!ft_main_thread(&data, 0, TRUE))
			break ;
	}
	ft_print_broadcast(&data, "Simulation ended");
	while (i < data.nb_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	return (ft_error(NONE, &data));
}
