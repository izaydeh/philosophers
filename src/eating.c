/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 03:12:47 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 20:32:40 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	update_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->current_time_of_meal_mutex);
	philo->current_time_of_meal = ft_gettime(philo, 1);
	pthread_mutex_unlock(&philo->data->current_time_of_meal_mutex);
	pthread_mutex_lock(&philo->data->meal_count_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->data->meal_count_mutex);
}

int	eating(t_philo *philo)
{
	update_meal(philo);
	return (sleep_philo(philo, philo->data->eating_time));
}

int	lock_forks_ordered(t_philo *philo, pthread_mutex_t **first,
		pthread_mutex_t **second)
{
	if (philo->left_mutex < philo->right_mutex)
	{
		*first = philo->left_mutex;
		*second = philo->right_mutex;
		philo->flag_fork = 1;
	}
	else
	{
		*first = philo->right_mutex;
		*second = philo->left_mutex;
		philo->flag_fork = 0;
	}
	return (0);
}

int	lock_forks(t_philo *philo, pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	if (checker_printf(philo, "\033[0;33mhas taken a fork\033[0m"))
	{
		pthread_mutex_unlock(first);
		return (1);
	}
	pthread_mutex_lock(second);
	if (checker_printf(philo, "\033[0;33mhas taken a fork\033[0m"))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	if (check_died_f(philo))
	{
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(first);
		return (1);
	}
	return (0);
}

int	manage_forks(t_philo *philo, int f)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (f)
	{
		if (lock_forks_ordered(philo, &first, &second))
			return (1);
		if (lock_forks(philo, first, second))
			return (1);
	}
	else
	{
		if (philo->flag_fork)
		{
			pthread_mutex_unlock(philo->right_mutex);
			pthread_mutex_unlock(philo->left_mutex);
		}
		else
		{
			pthread_mutex_unlock(philo->left_mutex);
			pthread_mutex_unlock(philo->right_mutex);
		}
	}
	return (0);
}
