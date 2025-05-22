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

int	validate_args(int argc, char **argv)
{
	int	i;
	int	value;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error: Wrong number of arguments\n", 34);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			write(2, "Error: Invalid argument (not a number)\n", 40);
			return (0);
		}
		value = ft_atoi(argv[i]);
		if (value <= 0)
		{
			write(2, "Error: Arguments must be greater than zero\n", 44);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_simulation(t_data *data, char **argv, pthread_t **threads)
{
	if (init_data(data, argv) || init_philos(data))
		return (1);
	*threads = malloc(data->num_of_philos * sizeof(pthread_t));
	if (!*threads)
	{
		cleanup(data, NULL, data->num_of_philos);
		return (ft_error("Malloc error"));
	}
	return (0);
}

int	start_simulation(t_data *data, pthread_t *threads)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine,
				&data->philos[i]) != 0)
		{
			ft_error("Failed to create thread");
			cleanup(data, threads, data->num_of_philos);
			return (1);
		}
		i++;
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
	{
		ft_error("Failed to create monitor thread");
		cleanup(data, threads, data->num_of_philos);
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	return (0);
}

void	end_simulation(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	cleanup(data, threads, data->num_of_philos);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	*threads;

	if (!validate_args(argc, argv))
		return (1);
	if (init_simulation(&data, argv, &threads))
		return (1);
	if (start_simulation(&data, threads))
		return (1);
	end_simulation(&data, threads);
	return (0);
}
