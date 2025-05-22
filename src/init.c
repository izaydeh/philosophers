/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:07:15 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/22 19:14:04 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_of_meals_must_eat = ft_atoi(argv[5]);
	else
		data->num_of_meals_must_eat = -1;
	data->simulation_ended = 0;
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			cleanup(data, NULL, i);
			return (ft_error("Fork mutex init error"));
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		cleanup(data, NULL, data->num_of_philos);
		return (ft_error("Print mutex init error"));
	}
	if (pthread_mutex_init(&data->sim_mutex, NULL) != 0)
	{
		cleanup(data, NULL, data->num_of_philos);
		return (ft_error("Sim mutex init error"));
	}
	return (0);
}

int	init_data(t_data *data, char **argv)
{
	struct timeval	tv;

	init_args(data, argv);
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->forks = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_error("Malloc error"));
	if (init_mutexes(data) != 0)
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(data->num_of_philos * sizeof(t_philo));
	if (!data->philos)
	{
		cleanup(data, NULL, data->num_of_philos);
		return (ft_error("Malloc error (philos)"));
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_of_philos;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
	return (0);
}
