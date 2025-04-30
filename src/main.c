/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:41:12 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 19:43:54 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(void *died_time)
{
	int	time_died;

	time_died = *(int *)died_time;
	printf("0\t philo[1] \033[0;33mhas taken a fork\033[0m\n");
	printf("%d\t philo[1] \033[1;31mdied\033[0m\n", time_died);
	return (NULL);
}

int	eating_one_philo(t_data *data)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, one_philo, &data->died_time))
	{
		printf("\033[1;31merror creating thread for the one philo\033[0m\n");
		return (1);
	}
	pthread_join(philo, NULL);
	return (0);
}

int	ft_thread(t_data *data)
{
	if (data->philos_count == 1)
	{
		if (eating_one_philo(data))
			return (1);
		return (0);
	}
	if (create_all_threads(data))
		return (1);
	monitor(data);
	join_threads(data);
	destroy_mutexes(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc != 5 && argc != 6) || init(&data, argv))
	{
		printf("\033[1;31mWrong in arguments\033[0m\n");
		return (1);
	}
	if (ft_thread(&data))
		return (1);
	return (0);
}
