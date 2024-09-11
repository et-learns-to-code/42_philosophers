/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:15:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/11 12:47:56 by etien            ###   ########.fr       */
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
# define FULL "is full\n"

typedef enum e_return
{
	SUCCESS,
	ARGS_ERR,
	MALLOC_ERR,
	THREAD_CREATE_ERR,
	THREAD_JOIN_ERR,
}	t_return;

typedef struct s_data	t_data;

// variables specific to a single philosopher
typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			last_meal;
	int				meals_eaten;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
}	t_philo;

// shared variables among all philosophers
typedef struct s_data
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	long			start_time;
	bool			dead_philo;
	int				full_philos;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	full_mutex;
}	t_data;

// Argument checking functions
int		correct_usage(void);
int		check_args(int ac, char **av);
int		args_not_digits(char **av);
int		invalid_args(char **av);
int		ft_atol(const char *str);

// Initialization functions
int		data_init(t_data *data, char **av);
void	philo_init(t_data *data);

// Philosopher routine functions
void	*philo_routine(void *arg);
void	philo_takes_forks(t_philo *philo);
void	philo_eats(t_philo *philo);
bool	is_philo_full(t_philo *philo);

// Death monitor functions
void	*check_philo_death(void *arg);
void	update_death(t_philo *philo);

// Time functions
long	timestamp(void);
void	ft_usleep(int ms);

// Mutex variable functions
void	print(t_philo *philo, char *msg);



#endif
