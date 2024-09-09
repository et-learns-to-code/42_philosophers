/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:15:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/09 15:47:55 by etien            ###   ########.fr       */
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

# define ARGS_ERR 1
# define MALLOC_ERR 2

# define TAKEN_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

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
	int				id;
	int				meals_eaten;
	int				last_meal_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_philo_state	philo_state;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nbr_meals;
	long			simulation_start;
	t_philo			*philos;
}	t_data;

int	correct_usage(void);
int		check_args(int ac, char **av);
int		args_not_digits(char **av);
int		invalid_args(char **av);
int		ft_atol(const char *str);

#endif
