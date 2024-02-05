/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:08:43 by disantam          #+#    #+#             */
/*   Updated: 2024/02/05 11:04:43 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_atoul(const char *str)
{
	size_t	result;
	int		sign;

	result = 0;
	sign = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	while ((*str == '-' || *str == '+') && (*str < '0' || *str > '9'))
	{
		if (*str != '-' && *str != '+')
			return (0);
		if (*str == '-')
			sign += 1;
		str++;
	}
	if (sign % 2 != 0)
		return (0);
	while (*str != '\0' && *str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result);
}

void	init_philos(t_data *program, t_philos *philos, pthread_mutex_t *mutex)
{
	size_t	i;

	i = -1;
	while (++i < program->nphilos)
	{
		philos[i].id = i + 1;
		philos[i].nphilos = program->nphilos;
		philos[i].dead = &program->dead_flag;
		philos[i].write_lock = &program->write_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].r_fork = mutex + i;
		philos[i].l_fork = mutex + i + 1;
		if (i + 1 == program->nphilos)
			philos[i].l_fork = mutex;
		philos[i].data = program;
		philos[i].meals = 0;
		philos[i].iseating = 0;
		philos[i].isfinished = 0;
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
	}
	program->philos = philos;
	program->forks = mutex;
}

int	parse_args(t_data *program, int argc, char **argv)
{
	program->nphilos = ft_atoi(argv[1]);
	program->ttd = ft_atoi(argv[2]);
	program->tte = ft_atoi(argv[3]);
	program->tts = ft_atoi(argv[4]);
	program->ntte = -1;
	if (program->nphilos <= 0 || program->ttd <= 0
		|| program->tte <= 0 || program->tts <= 0)
	{
		return (1);
	}
	if (argc == 6)
	{
		program->ntte = ft_atoi(argv[5]);
		if (program->ntte <= 0)
			return (1);
	}
	program->dead_flag = 0;
	return (0);
}
