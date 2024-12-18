/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:15:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 16:33:29 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// semaphores
# include <semaphore.h>
// oflag for sem_open
# include <fcntl.h>
// waitpid
# include <sys/wait.h>
// SIGTERM
# include <signal.h>
// pthread
# include <pthread.h>
// printf
# include <stdio.h>
// malloc, free
# include <stdlib.h>
// fork, usleep
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

typedef struct s_philo	t_philo;

// every forked process will get a copy of these variables
typedef struct s_data
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
	t_philo			*philos;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*meal_sem;
	long long		start_time;
}	t_data;

// meal variables have to be atomic to avoid data race
// An atomic variable refers to a variable that is accessed atomically,
// meaning that its operations (like read, write, increment) are indivisible
// and cannot be interrupted by other threads or processes.
typedef struct s_philo
{
	t_data					*data;
	int						id;
	_Atomic int				meals_eaten;
	_Atomic long long		last_meal;
}	t_philo;

// Argument checking functions
void		correct_usage(void);
bool		incorrect_args(int ac, char **av);
bool		args_not_digits(char **av);
bool		invalid_args(char **av);

// Initialization functions
int			data_init(t_data *data, char **av);
int			malloc_philos(t_data *data);
void		philo_init(t_data *data);

// Simulation start and end functions
int			run_simulation(t_data *data);
int			fork_philos(t_data *data, int i, pid_t *philos_pid);
void		recover_philos(t_data *data, pid_t *philos_pid);

// Philosopher routine function
void		*philo_routine(t_philo *philo);

// Philosopher actions functions
bool		philo_eats_and_check_full(t_philo *philo);
void		philo_is_eating(t_philo *philo);
void		philo_sleeps(t_philo *philo);
void		philo_thinks(t_philo *philo);

// Death checking function
void		*check_philo_death(void *arg);

// Util functions
void		print(t_philo *philo, char *msg);
int			ft_atoi(const char *str);

// Time function
void		ft_usleep(int ms);

// Clean up function in main.c
void		clean_up(t_data *data);

#endif
