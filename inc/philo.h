/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:29:05 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/14 13:59:05 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
	int				simulation_ended;
	long			start_time;
	struct s_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			last_meal;
	int				meals_eaten;
	t_data			*data;
}	t_philo;

// Routine
void	*philo_routine(void *arg);
void	take_forks(t_philo *philo);
void	eat_and_sleep(t_philo *philo);

// Monitor
void	*monitor(void *arg);

// Utils
void	cleanup(t_data *data, pthread_t *threads);
long	get_time(t_data *data);
void	my_sleep(t_data *data, long ms);
void	print_action(t_philo *philo, char *str);
int		ft_error(char *msg);
int		ft_atoi(const char *str);
int		validate_args(int argc, char **argv);

#endif