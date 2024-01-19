/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:11:13 by disantam          #+#    #+#             */
/*   Updated: 2024/01/19 14:29:58 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	*philo_routine(void	*philosopher);
// int	init_threads(t_data *program, t_philos *philos,
// 				pthread_mutex_t *mutex, pthread_t *threads);
// int	join_threads(t_data *program, pthread_mutex_t *mutex, pthread_t *threads);

void	*philo_routine(void	*philosopher)
{
	t_philos		*philo;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;

	philo = (t_philos *)philosopher;
	r_fork = (pthread_mutex_t *)&philo->data->forks[philo->id - 1];
	l_fork = (pthread_mutex_t *)&philo->data->forks[philo->id];
	while (*philo->dead != 1)
	{
		printf("%ld %d is thinking\n", get_time(), philo->id);
	}
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
		if (pthread_create(&threads[i], NULL, &philo_routine,
			(void *)&philos[i]) != 0)
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
	return (0);
}

int main(int argc, char *argv[])
{
	t_data			program;
	pthread_mutex_t	mutex[200];
	t_philos		philos[200];
	pthread_t		threads[200];

	if (argc < 5)
		return (1);
	if (parse_args(&program, argc, argv) != 0)
	{
		return (1);
	}
	init_philos(&program, philos, mutex);
	if (init_threads(&program, philos, mutex, threads) != 0)
	{
	 	return (1);
	}
	if (join_threads(&program, mutex, threads) != 0)
	{
		return (1);
	}
	return (0);
}
