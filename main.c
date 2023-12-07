/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:21 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/07 04:01:49 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(int ac, char **av, t_data *data)
{
	t_error	err;

	ft_init_data(data);
	if (ac < 5 || ac > 6)
		ft_error(ARGC_ERROR, data);
	err = ft_parse(data, ac - 1, av + 1);
	if (err != NONE)
		ft_error(err, data);
	err = ft_init_simulation(data);
	if (err != NONE)
		ft_error(err, data);
	err = ft_start(data);
	if (err != NONE)
		ft_error(err, data);
}

t_bool	ft_main_thread(t_data *data, int i, t_bool all_full)
{
	while (i < data->nb_philo)
	{
		if (data->philo[i].state != FULL)
			all_full = FALSE;
		if (ft_get_time(data) - data->philo[i].last_meal > data->time_to_die
			&& data->philo[i].state != FULL)
		{
			ft_print_action(data, i, DIE);
			data->state = ENDED;
			return (FALSE);
		}
		pthread_mutex_lock(&data->philo[i].mutex);
		data->philo[i].last_meal += USLEEP;
		pthread_mutex_unlock(&data->philo[i].mutex);
		ft_usleep(USLEEP);
		i++;
	}
	if (all_full)
	{
		ft_print_broadcast(data, "All philosophers are full");
		data->state = ENDED;
		return (FALSE);
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	ft_init(ac, av, &data);
	while (data.state != ENDED)
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
