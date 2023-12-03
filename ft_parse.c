/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 01:21:48 by ysabik            #+#    #+#             */
/*   Updated: 2023/12/03 15:40:37 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int			i;
	long long	nb;

	i = 0;
	nb = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i] && (str[i] >= '0' && str[i] <= '9') && nb <= 2147483647)
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] != '\0' || nb > 2147483647)
		return (-1);
	return (nb);
}

static int	ft_fill_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[0]);
	data->time_to_die = ft_atoi(av[1]);
	data->time_to_eat = ft_atoi(av[2]);
	data->time_to_sleep = ft_atoi(av[3]);
	if (ac == 5)
		data->nb_meal = ft_atoi(av[4]);
	else
		data->nb_meal = -1;
	if (data->nb_philo < 2)
		return (-1);
	return (0);
}

int	ft_parse(t_data *data, int ac, char **av)
{
	if (ft_atoi(av[0]) == -1
		|| ft_atoi(av[1]) == -1
		|| ft_atoi(av[2]) == -1
		|| ft_atoi(av[3]) == -1
		|| (ac == 5 && ft_atoi(av[4]) == -1)
		|| ft_fill_data(data, ac, av) == -1)
	{
		printf("Error: Invalid argument\n");
		return (-1);
	}
	return (0);
}
