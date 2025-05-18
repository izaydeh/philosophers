/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhalil <ikhalil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:49:21 by ikhalil           #+#    #+#             */
/*   Updated: 2025/05/17 15:50:33 by ikhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->data->num_of_philos == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "\033[1;93mhas taken a fork\033[0m");
		philo->last_meal = get_time(philo->data);
		my_sleep(philo->data, philo->data->time_to_die + 10);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "\033[1;93mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, "\033[1;93mhas taken a fork\033[0m");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_action(philo, "\033[1;93mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "\033[1;93mhas taken a fork\033[0m");
	}
}

void	eat_and_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->sim_mutex);
	philo->last_meal = get_time(philo->data);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->sim_mutex);
	print_action(philo, "\033[1;92mis eating\033[0m");
	my_sleep(philo->data, philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	print_action(philo, "\033[1;96mis sleeping\033[0m");
	my_sleep(philo->data, philo->data->time_to_sleep);
	print_action(philo, "\033[1;95mis thinking\033[0m");
}

static int	should_exit_simulation(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->sim_mutex);
	ended = data->simulation_ended;
	pthread_mutex_unlock(&data->sim_mutex);
	return (ended);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (should_exit_simulation(philo->data))
			break ;
		take_forks(philo);
		if (philo->data->num_of_philos == 1)
			continue ;
		if (should_exit_simulation(philo->data))
		{
			pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
			pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
			break ;
		}
		eat_and_sleep(philo);
	}
	return (NULL);
}
