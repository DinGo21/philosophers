/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:09:33 by disantam          #+#    #+#             */
/*   Updated: 2024/02/05 11:24:46 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t miliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < miliseconds)
	{
		usleep(miliseconds / 10);
	}
	return (0);
}

void	print_status(t_philos *p, char *message)
{
	pthread_mutex_lock(p->write_lock);
	if (*p->dead != 1)
		printf("%ld %d %s\n", get_time() - p->start_time, p->id, message);
	pthread_mutex_unlock(p->write_lock);
}

void	destroy_mutex(t_data *program, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (++i < program->nphilos)
	{
		pthread_mutex_destroy(&mutex[i]);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->dead_lock);
}
