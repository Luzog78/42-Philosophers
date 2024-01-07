/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:21 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/05 17:17:30 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	if (err == PROCESS_END)
		return (1);
	return (0);
}

t_bool	ft_main_thread(t_data *data, int i, t_bool all_full)
{
	while (i < data->nb_philo)
	{
		if (ft_get_philo_state(&data->philo[i]) != FULL)
			all_full = FALSE;
		if (ft_get_time(data) - data->philo[i].last_meal > data->time_to_die
			&& ft_get_philo_state(&data->philo[i]) != FULL)
		{
			ft_set_data_state(data, ENDED);
			ft_print_action(data, i, DIE);
			return (FALSE);
		}
		//ft_usleep(USLEEP);
		i++;
	}
	if (all_full)
	{
		ft_print_broadcast(data, "All philosophers are full");
		ft_set_data_state(data, ENDED);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ft_init(ac, av, &data))
		return (1);
	while (ft_get_data_state(&data) != ENDED)
	{
		if (!ft_main_thread(&data, 0, TRUE))
			break ;
	}
	while (i < data.nb_philo)
	{
		pthread_detach(data.philo[i].thread);
		i++;
	}
	ft_print_broadcast(&data, "Simulation ended");
	return (ft_error(NONE, &data));
}
