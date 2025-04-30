/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 00:42:23 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 13:30:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->current_time_of_meal_mutex, NULL)
		|| pthread_mutex_init(&data->printf_mutex, NULL)
		|| pthread_mutex_init(&data->meal_count_mutex, NULL)
		|| pthread_mutex_init(&data->can_print_mutex, NULL)
		|| pthread_mutex_init(&data->begin_time_mutex, NULL))
		return (1);
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		data->philos[i].who_i_am = i;
		data->philos[i].meal_count = 0;
		data->philos[i].current_time_of_meal = 0;
		data->philos[i].data = data;
		data->philos[i].right_mutex = &data->forks[i];
		if (i != data->philos_count - 1)
			data->philos[i].left_mutex = &data->forks[i + 1];
		else
			data->philos[i].left_mutex = &data->forks[0];
		i++;
	}
	return (0);
}

int	init_meal_num(t_data *data, char *str)
{
	if (!ft_isdigit(str))
		return (1);
	data->meal_num = ft_atoi(str);
	if (data->meal_num <= 0)
		return (1);
	return (0);
}

int	init(t_data *data, char **argv)
{
	if (!ft_isdigit(argv[1]) || !ft_isdigit(argv[2]) || !ft_isdigit(argv[3])
		|| !ft_isdigit(argv[4]))
		return (1);
	data->philos_count = ft_atoi(argv[1]);
	data->died_time = ft_atoi(argv[2]);
	data->eating_time = ft_atoi(argv[3]);
	data->sleeping_time = ft_atoi(argv[4]);
	data->meal_num = -1;
	data->the_begin_time = 0;
	data->can_print = 1;
	if (argv[5])
	{
		if (init_meal_num(data, argv[5]))
			return (1);
	}
	if (data->philos_count <= 0 || data->died_time <= 0
		|| data->eating_time <= 0 || data->sleeping_time <= 0
		|| data->philos_count > 250)
		return (1);
	if (init_mutex(data))
		return (1);
	if (init_philo(data))
		return (1);
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->meal_count_mutex);
	pthread_mutex_destroy(&data->printf_mutex);
	pthread_mutex_destroy(&data->current_time_of_meal_mutex);
	pthread_mutex_destroy(&data->can_print_mutex);
	pthread_mutex_destroy(&data->begin_time_mutex);
}
