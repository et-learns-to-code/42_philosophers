/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:15:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/17 11:28:08 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// pthread, mutexes
# include <pthread.h>
// printf
# include <stdio.h>
// malloc, free
# include <stdlib.h>
// usleep
# include <unistd.h>
// gettimeofday
# include <sys/time.h>
// boolean data type
# include <stdbool.h>

# define TAKEN_FORK "has taken a fork\n"
# define EAT "is eating\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIED "died\n"

typedef struct s_data	t_data;

// variables specific to a single philosopher thread
typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
}	t_philo;

// shared variables among all philosopher threads
typedef struct s_data
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	long			start_time;
	bool			dead_philo;
	bool			stop_simulation;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	death_mutex;
}	t_data;

// Argument checking functions
void	correct_usage(void);
bool	incorrect_args(int ac, char **av);
bool	args_not_digits(char **av);
bool	invalid_args(char **av);

// Initialization functions
int		data_init(t_data *data, char **av);
int		malloc_philos_forks(t_data *data);
void	philo_init(t_data *data);
int		run_simulation(t_data *data);

// Philosopher routine function
void	*philo_routine(void *arg);

// Philosopher actions functions
bool	philo_eats_and_check_full(t_philo *philo);
void	philo_is_eating(t_philo *philo);
bool	philo_is_full(t_philo *philo);
void	philo_sleeps(t_philo *philo);
void	philo_thinks(t_philo *philo);

// Death checking functions
void	*check_philo_death(void *arg);
void	set_philo_dead(t_philo *philo);
bool	any_philo_dead(t_philo *philo);

// Util functions
void	print(t_philo *philo, char *msg);
long	ft_atol(const char *str);

// Time functions
long	timestamp(void);
void	ft_usleep(int ms);

// Clean up function in main.c
void	clean_up(t_data *data);

#endif
