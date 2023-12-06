/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:21 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/06 18:46:58 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (data->philo[i].thread)
			pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_error	err;

	/*int ac = 6;
	char *av[7] = {NULL};
	av[1] = "1";
	av[2] = "800";
	av[3] = "200";
	av[4] = "200";
	av[5] = "7";*/
	ft_init_data(&data);
	if (ac < 5 || ac > 6)
		return (ft_error(ARGC_ERROR, &data));
	err = ft_parse(&data, ac - 1, av + 1);
	if (err != NONE)
		return (ft_error(err, &data));
	err = ft_init(&data);
	if (err != NONE)
		return (ft_error(err, &data));
	err = ft_start(&data);
	if (err != NONE)
		return (ft_error(err, &data));
	while (data.state != ENDED)
	{
		int i = 0;
		t_bool all_full = TRUE;
		while (i < data.nb_philo)
		{
			if (data.philo[i].state != FULL)
				all_full = FALSE;
			if (ft_get_time(&data) - data.philo[i].last_meal.tv_sec > data.time_to_die
				&& data.philo[i].state != FULL)
			{
				ft_print_action(&data, i, DIE);
				data.state = ENDED;
				break ;
			}
			usleep(USLEEP);
			i++;
		}
		if (all_full)
		{
			ft_print_broadcast(&data, "All philosophers are full");
			data.state = ENDED;
			break ;
		}
	}
	int i = 0;
	while (i < data.nb_philo)
	{
		pthread_detach(data.philo[i].thread);
		i++;
	}
	ft_print_broadcast(&data, "Simulation ended");
	return (ft_error(NONE, &data));
}
