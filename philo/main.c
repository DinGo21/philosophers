/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:13 by disantam          #+#    #+#             */
/*   Updated: 2024/01/24 17:57:07 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *program)
{
	size_t		i;
	size_t		finished;
	t_data		*data;
	t_philos	*philos;

	data = (t_data *)program;
	philos = (t_philos *)data->philos;
	i = 0;
	finished = 0;
	while (data->dead_flag != 1)
	{
		if (isdead(data, philos + i) == 1)
		{
			print_status(philos + i, "died");
			data->dead_flag = 1;
		}
		check_philo(data, philos + i, &finished);
		if (++i >= data->nphilos)
			i = 0;
	}
	return (NULL);
}

void	*philo_routine(void	*philosopher)
{
	t_philos		*philo;

	philo = (t_philos *)philosopher;
	philo->start_time = get_time();
	while (*philo->dead != 1)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		iseating(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		issleeping(philo);
	}
	// pthread_mutex_unlock(philo->dead_lock);
	return (NULL);
}

int	init_threads(t_data *program, t_philos *philos,
				pthread_mutex_t *mutex, pthread_t *threads)
{
	size_t	i;

	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
		{
			return (1);
		}
	}
	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine, &philos[i]) != 0)
		{
			return (1);
		}
	}
	return (0);
}

int	join_threads(t_data *program, pthread_mutex_t *mutex, pthread_t *threads)
{
	size_t	i;

	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			return (1);
		}
	}
	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_mutex_destroy(&mutex[i]) != 0)
		{
			return (1);
		}
	}
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	return (0);
}

int main(int argc, char *argv[])
{
	t_data			program;
	pthread_mutex_t	mutex[200];
	t_philos		philos[200];
	pthread_t		threads[200];
	pthread_t		monitor;

	if (argc < 5)
		return (1);
	if (parse_args(&program, argc, argv) != 0)
		return (1);
	init_philos(&program, philos, mutex);
	if (init_threads(&program, philos, mutex, threads) != 0)
	{
	 	return (1);
	}
	pthread_create(&monitor, NULL, &monitor_routine, &program);
	if (join_threads(&program, mutex, threads) != 0)
	{
		return (1);
	}
	pthread_join(monitor, NULL);
	return (0);
}
