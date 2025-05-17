/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:49:31 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/14 17:55:12 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_time(t_data *data, long now)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (now - data->philos[i].last_meal >= data->time_to_die)
			return (i);
		i++;
	}
	return (-1);
}

static int	check_meal(t_data *data)
{
	int	i;
	int	all_full;

	if (data->num_of_meals_must_eat == -1)
		return (0);
	i = 0;
	all_full = 1;
	while (i < data->num_of_philos)
	{
		if (data->philos[i].meals_eaten < data->num_of_meals_must_eat)
		{
			all_full = 0;
			break ;
		}
		i++;
	}
	if (all_full)
		return (1);
	return (0);
}

static void	handle_death(t_data *data, int dead, long now)
{
	pthread_mutex_lock(&data->sim_mutex);
	data->simulation_ended = 1;
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld %d \033[1;31mdied\033[0m\n", now, dead + 1);
	pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_unlock(&data->sim_mutex);
}

static int	monitor_cycle(t_data *data, long *now)
{
	int	dead;

	usleep(1000);
	pthread_mutex_lock(&data->sim_mutex);
	if (data->simulation_ended)
	{
		pthread_mutex_unlock(&data->sim_mutex);
		return (0);
	}
	*now = get_time(data);
	dead = check_time(data, *now);
	pthread_mutex_unlock(&data->sim_mutex);
	if (dead >= 0)
	{
		handle_death(data, dead, *now);
		return (0);
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_data	*data;
	long	now;

	data = (t_data *)arg;
	while (monitor_cycle(data, &now))
	{
		pthread_mutex_lock(&data->sim_mutex);
		if (check_meal(data))
		{
			data->simulation_ended = 1;
			pthread_mutex_unlock(&data->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->sim_mutex);
	}
	return (NULL);
}
