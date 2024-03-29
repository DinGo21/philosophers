/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:13 by disantam          #+#    #+#             */
/*   Updated: 2024/02/05 11:27:07 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitor_routine(void *program)
{
	int			i;
	int			finished;
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
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			break ;
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
	if ((philo->id) % 2 == 0)
		ft_usleep(1);
	while (*philo->dead != 1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		if (philo->nphilos == 1)
		{
			ft_usleep(philo->data->ttd);
			pthread_mutex_unlock(philo->r_fork);
			break ;
		}
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		eating(philo);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		sleeping(philo);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

int	init_threads(t_data *program, pthread_mutex_t *mutex,
				pthread_t *threads, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_mutex_init(&mutex[i], NULL) != 0)
			return (1);
	}
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine,
				&program->philos[i]) != 0)
			return (1);
	}
	if (pthread_create(monitor, NULL, &monitor_routine, program) != 0)
		return (1);
	return (0);
}

int	join_threads(t_data *program, pthread_mutex_t *mutex,
				pthread_t *threads, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < program->nphilos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (1);
	}
	if (pthread_join(*monitor, NULL) != 0)
		return (1);
	i = -1;
	while (++i < program->nphilos)
	{
		pthread_mutex_destroy(&mutex[i]);
	}
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	return (0);
}

int	main(int argc, char *argv[])
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
	if (init_threads(&program, mutex, threads, &monitor) != 0)
	{
		return (destroy_mutex(&program, mutex), 1);
	}
	if (join_threads(&program, mutex, threads, &monitor) != 0)
	{
		return (destroy_mutex(&program, mutex), 1);
	}
	return (0);
}
