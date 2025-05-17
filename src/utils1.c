/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:49:45 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/14 12:40:15 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->sim_mutex);
	free(data->forks);
	free(data->philos);
	free(threads);
}

long	get_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - data->start_time);
}

void	my_sleep(t_data *data, long ms)
{
	long	start;

	start = get_time(data);
	while (get_time(data) - start < ms)
	{
		pthread_mutex_lock(&data->sim_mutex);
		if (data->simulation_ended)
		{
			pthread_mutex_unlock(&data->sim_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->sim_mutex);
		usleep(100);
	}
}

void	print_action(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->sim_mutex);
	if (!philo->data->simulation_ended)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %d %s\n",
			get_time(philo->data),
			philo->id + 1,
			str);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->sim_mutex);
}

int	ft_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
	write(2, "\n", 1);
	return (1);
}
