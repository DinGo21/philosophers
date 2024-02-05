/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:13 by disantam          #+#    #+#             */
/*   Updated: 2024/02/05 10:18:58 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isdead(t_data *data, t_philos *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= data->ttd && philo->iseating != 1)
	{
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	}
	return (pthread_mutex_unlock(philo->meal_lock), 0);
}

int	check_philo(t_data *data, t_philos *philo, size_t *finished)
{
	if (philo->meals >= data->ntte && data->ntte != -1
		&& philo->isfinished != 1)
	{
		philo->isfinished = 1;
		*finished += 1;
	}
	if (*finished == data->nphilos)
	{
		data->dead_flag = 1;
		return (1);
	}
	return (0);
}

void	eating(t_philos *philo)
{
	philo->iseating = 1;
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->meals += 1;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->data->tte);
	philo->iseating = 0;
}

void	sleeping(t_philos *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->tts);
}
