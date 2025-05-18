/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:49:38 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/14 13:41:32 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_data *data, char **argv)
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

static int	init_data(t_data *data, char **argv)
{
	struct timeval	tv;
	int				i;

	init_args(data, argv);
	gettimeofday(&tv, NULL);
	data->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->forks = malloc(data->num_of_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (ft_error("Malloc error"));
	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->sim_mutex, NULL);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(data->num_of_philos * sizeof(t_philo));
	if (!data->philos)
		return (ft_error("Malloc error"));
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

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;
	pthread_t	monitor_thread;
	int			i;

	if (!validate_args(argc, argv))
		return (1);
	if (init_data(&data, argv) || init_philos(&data))
		return (1);
	threads = malloc(data.num_of_philos * sizeof(pthread_t));
	if (!threads)
		return (ft_error("Malloc error"));
	i = -1;
	while (++i < data.num_of_philos)
		pthread_create(&threads[i], NULL, philo_routine, &data.philos[i]);
	pthread_create(&monitor_thread, NULL, monitor, &data);
	pthread_join(monitor_thread, NULL);
	i = -1;
	while (++i < data.num_of_philos)
		pthread_join(threads[i], NULL);
	cleanup(&data, threads);
	return (0);
}
