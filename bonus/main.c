/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysabik <ysabik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 03:07:21 by ysabik            #+#    #+#             */
/*   Updated: 2024/01/08 17:37:56 by ysabik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_wait(char *name);
void ft_post(char *name);

int	ft_init(int ac, char **av, t_data *data)
{
	t_error	err;

	if (ac < 5 || ac > 6)
		return (ft_error(ARGC_ERROR, data));
	ft_init_data(data);
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

void	*ft_death_waiter(void *arg)
{
	t_data	*data;
	sem_t	*sem;
	
	data = (t_data *) arg;
	sem = sem_open(DIES_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return (NULL);
	sem_wait(sem);
	sem_close(sem);
	ft_kill(data);
	ft_print_broadcast(data, "A philosopher died");
	ft_post(START_SEM);
	return (NULL);
}

void	*ft_full_waiter(void *arg)
{
	t_data	*data;
	sem_t	*sem;
	int		i;
	
	data = (t_data *) arg;
	sem = sem_open(FULLS_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return (NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		sem_wait(sem);
		i++;
	}
	sem_close(sem);
	ft_kill(data);
	ft_print_broadcast(data, "All philosophers are full");
	ft_post(START_SEM);
	return (NULL);
}

void	ft_start_threads(t_data *data)
{
	if (pthread_create(&data->death_waiter, NULL, ft_death_waiter, data)
		|| pthread_create(&data->full_waiter, NULL, ft_full_waiter, data))
		ft_error(THREAD_ERROR, data);
}

// clear ; make re ; echo "" ;
// echo "      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" ; echo "" ;
// valgrind --tool=helgrind --track-lockorders=no --history-level=full -s --
// ./philo 100 700 200 200 2

void	ft_end(t_data *data)
{
	sem_t	*sem;
	int		i;

	sem = sem_open(PRINT_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	sem_wait(sem);
	data->can_print = FALSE;
	sem_post(sem);
	sem_close(sem);
	ft_post(DIES_SEM);
	sem = sem_open(FULLS_SEM, O_RDWR);
	if (sem == SEM_FAILED)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		sem_post(sem);
		i++;
	}
	sem_close(sem);
	pthread_join(data->death_waiter, NULL);
	pthread_join(data->full_waiter, NULL);
	ft_print_broadcast(data, "Simulation ended");
}

int	main(int ac, char **av)
{
	t_data		data;

	if (ft_init(ac, av, &data))
		return (1);
	if (data.is_main_process)
	{
		ft_start_threads(&data);
		ft_wait(START_SEM);
		ft_end(&data);
	}
	else {
		ft_philo(&data);
	}
	return (ft_error(NONE, &data));
}
