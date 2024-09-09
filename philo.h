/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:15:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/09 18:34:00 by etien            ###   ########.fr       */
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

# define TAKEN_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef enum e_return
{
	SUCCESS,
	ARGS_ERR,
	MALLOC_ERR,
	THREAD_CREATE_ERR,
	THREAD_JOIN_ERR,
}	t_return;

typedef enum e_philo_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FULL
}	t_philo_state;

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	pthread_t		thread;
	t_philo_state	philo_state;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	long			start_time;
	t_philo			*philos;
	pthread_t		death_monitor;
	pthread_t		full_monitor;
	pthread_mutex_t	print;
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

// Time functions
long	timestamp(void);
void	ft_usleep(int ms);

// Mutex variable functions
void	print(t_philo *philo, char *msg);



#endif
