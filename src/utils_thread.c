/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:42:00 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 20:32:40 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettime(t_philo *philo, int f)
{
	struct timeval	c_time;
	long			current_time;
	long			begin_time;

	gettimeofday(&c_time, NULL);
	current_time = (c_time.tv_sec * 1000000 + c_time.tv_usec) / 1000;
	if (f)
	{
		pthread_mutex_lock(&philo->data->begin_time_mutex);
		begin_time = philo->data->the_begin_time;
		pthread_mutex_unlock(&philo->data->begin_time_mutex);
		return (current_time - begin_time);
	}
	return (current_time);
}

int	checker_printf(t_philo *philo, char *msg)
{
	long	timepilo;

	pthread_mutex_lock(&philo->data->can_print_mutex);
	if (!philo->data->can_print)
	{
		pthread_mutex_unlock(&philo->data->can_print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->can_print_mutex);
	pthread_mutex_lock(&philo->data->can_print_mutex);
	pthread_mutex_lock(&philo->data->printf_mutex);
	timepilo = ft_gettime(philo, 1);
	if (philo->data->can_print)
		printf("%ld\t philo[%d] %s\n", timepilo, philo->who_i_am + 1, msg);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	pthread_mutex_unlock(&philo->data->can_print_mutex);
	return (0);
}

int	sleep_philo(t_philo *philo, int time)
{
	long	start;
	long	now;

	start = ft_gettime(philo, 1);
	while (1)
	{
		usleep(50);
		now = ft_gettime(philo, 1);
		if (check_died_f(philo) || (now - start >= time))
			break ;
	}
	return (0);
}
