/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:41:31 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 20:32:40 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->id_creat % 2 == 0)
		usleep(1000);
	while (!check_died_f(philo))
	{
		if (dinner(philo))
			break ;
		if (check_died_f(philo))
			break ;
		if (checker_printf(philo, "\033[0;36mis sleeping\033[0m"))
			break ;
		if (sleep_philo(philo, philo->data->sleeping_time))
			break ;
		if (check_died_f(philo))
			break ;
		if (checker_printf(philo, "\033[0;35mis thinking\033[0m"))
			break ;
	}
	return (NULL);
}

int	check_died_f(t_philo *philo)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&philo->data->current_time_of_meal_mutex);
	time_since_last_meal = ft_gettime(philo, 1) - philo->current_time_of_meal;
	pthread_mutex_unlock(&philo->data->current_time_of_meal_mutex);
	return (time_since_last_meal > philo->data->died_time);
}

int	dinner(t_philo *philo)
{
	if (manage_forks(philo, 1))
		return (1);
	if (checker_printf(philo, "\033[0;32mis eating\033[0m"))
	{
		manage_forks(philo, 0);
		return (1);
	}
	if (eating(philo))
	{
		manage_forks(philo, 0);
		return (1);
	}
	manage_forks(philo, 0);
	return (0);
}
