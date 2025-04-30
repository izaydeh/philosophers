/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:34:01 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 20:35:01 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_join(data->philos[i].id_creat, NULL);
		i++;
	}
}

int	create_all_threads(t_data *data)
{
	int	i;

	pthread_mutex_lock(&data->begin_time_mutex);
	data->the_begin_time = ft_gettime(NULL, 0);
	pthread_mutex_unlock(&data->begin_time_mutex);
	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_lock(&data->current_time_of_meal_mutex);
		data->philos[i].current_time_of_meal = data->the_begin_time;
		pthread_mutex_unlock(&data->current_time_of_meal_mutex);
		if (pthread_create(&data->philos[i].id_creat, NULL, routine_philo,
				&data->philos[i]))
		{
			pthread_mutex_lock(&data->printf_mutex);
			printf("\033[1;31merror creating thread philo[%d]\033[0m\n", i + 1);
			pthread_mutex_unlock(&data->printf_mutex);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int	check_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->current_time_of_meal_mutex);
	time_since_last_meal = ft_gettime(&data->philos[i], 1)
		- data->philos[i].current_time_of_meal;
	pthread_mutex_unlock(&data->current_time_of_meal_mutex);
	if (time_since_last_meal > data->died_time)
	{
		pthread_mutex_lock(&data->can_print_mutex);
		if (data->can_print)
		{
			pthread_mutex_lock(&data->printf_mutex);
			printf("%ld\t philo[%d] \033[1;31mdied\033[0m\n",
				ft_gettime(&data->philos[i], 1), i + 1);
			pthread_mutex_unlock(&data->printf_mutex);
			data->can_print = 0;
		}
		pthread_mutex_unlock(&data->can_print_mutex);
		return (1);
	}
	return (0);
}

int	check_all_eaten(t_data *data, int *all_eaten, int i)
{
	pthread_mutex_lock(&data->meal_count_mutex);
	if (data->meal_num != -1 && data->philos[i].meal_count < data->meal_num)
		*all_eaten = 0;
	pthread_mutex_unlock(&data->meal_count_mutex);
	return (*all_eaten);
}

void	monitor(t_data *data)
{
	int	all_eaten;
	int	i;

	while (1)
	{
		all_eaten = 1;
		i = 0;
		while (i < data->philos_count)
		{
			if (check_death(data, i))
				return ;
			check_all_eaten(data, &all_eaten, i);
			i++;
		}
		if (all_eaten && data->meal_num != -1)
		{
			pthread_mutex_lock(&data->can_print_mutex);
			data->can_print = 0;
			pthread_mutex_unlock(&data->can_print_mutex);
			return ;
		}
		usleep(500);
	}
}
