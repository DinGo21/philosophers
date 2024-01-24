/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:43:13 by disantam          #+#    #+#             */
/*   Updated: 2024/01/24 17:07:08 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isdead(t_data *data, t_philos *philo)
{
	if (get_time() - philo->start_time >= data->ttd && philo->iseating != 1 &&
		philo->meals == 0)
	{
		return (1);
	}
	if (get_time() - philo->last_meal >= data->ttd && philo->iseating != 1 &&
		philo->meals > 0)
	{
		return (1);
	}
	return (0);
}

int	check_philo(t_data *data, t_philos *philo, size_t *finished)
{
	if (philo->meals >= data->ntte && data->ntte != -1 &&
		philo->isfinished != 1)
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

void	iseating(t_philos *philo)
{
	print_status(philo, "is eating");
	philo->last_meal = get_time();
	philo->iseating = 1;
	philo->meals += 1;
	ft_usleep(philo->data->tte);
}

void	issleeping(t_philos *philo)
{
	philo->iseating = 0;
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->tts);
}