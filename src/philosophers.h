/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: disantam <disantam@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:10:24 by disantam          #+#    #+#             */
/*   Updated: 2024/02/05 11:27:29 by disantam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos
{
	int				id;
	int				nphilos;
	int				*dead;
	int				iseating;
	int				meals;
	int				isfinished;
	size_t			last_meal;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	struct s_data	*data;
}					t_philos;

typedef struct s_data
{
	int				dead_flag;
	int				ntte;
	int				nphilos;
	size_t			ttd;
	size_t			tte;
	size_t			tts;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	*forks;
	t_philos		*philos;
}					t_data;

/* parse.c */
int		ft_atoi(const char *str);
size_t	ft_atoul(const char *str);
int		parse_args(t_data *program, int argc, char **argv);
void	init_philos(t_data *program, t_philos *philos, pthread_mutex_t *mutex);

/* routine.c */
int		isdead(t_data *data, t_philos *philo);
int		check_philo(t_data *data, t_philos *philo, int *finished);
void	eating(t_philos *philo);
void	sleeping(t_philos *philo);

/* utils.c */
size_t	get_time(void);
int		ft_usleep(size_t miliseconds);
void	print_status(t_philos *p, char *message);
void	destroy_mutex(t_data *program, pthread_mutex_t *mutex);

#endif
