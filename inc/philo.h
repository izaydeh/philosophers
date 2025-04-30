/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-kawa <sal-kawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:39:22 by marvin            #+#    #+#             */
/*   Updated: 2025/04/30 20:32:40 by sal-kawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					who_i_am;
	int					i_am_dead;
	int					meal_count;
	int					flag_fork;
	long				current_time_of_meal;
	pthread_t			id_creat;
	pthread_mutex_t		*right_mutex;
	pthread_mutex_t		*left_mutex;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					philos_count;
	int					eating_time;
	int					meal_num;
	int					sleeping_time;
	int					died_time;
	int					can_print;
	long				the_begin_time;
	pthread_t			monitor;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		meal_count_mutex;
	pthread_mutex_t		printf_mutex;
	pthread_mutex_t		current_time_of_meal_mutex;
	pthread_mutex_t		can_print_mutex;
	pthread_mutex_t		begin_time_mutex;
	t_philo				philos[250];
}						t_data;

//rotene
void					*routine_philo(void *philo);
int						check_died_f(t_philo *philo);
//sleep
int						ft_sleep(t_philo *philo);
//think
int						think(t_philo *philo);
//eat
void					update_meal(t_philo *philo);
int						eating(t_philo *philo);
int						manage_forks(t_philo *philo, int f);
int						dinner(t_philo *philo);
int						lock_forks_ordered(t_philo *philo,
							pthread_mutex_t **first,
							pthread_mutex_t **second);
int						lock_second_fork(t_philo *philo,
							pthread_mutex_t *first,
							pthread_mutex_t *second);
//init
int						init_mutex(t_data *data);
int						init_philo(t_data *data);
int						init(t_data *data, char **argv);
//threads.c
int						create_all_threads(t_data *data);
void					join_threads(t_data *data);
void					destroy_mutexes(t_data *data);
void					monitor(t_data *data);
int						check_death(t_data *data, int i);
int						check_all_eaten(t_data *data, int *all_eaten, int i);
//utilsthread
long					ft_gettime(t_philo *philo, int f);
int						checker_printf(t_philo *philo, char *msg);
int						sleep_philo(t_philo *philo, int time);
//utils
int						ft_atoi(char *s);
int						ft_isdigit(char *s);

#endif