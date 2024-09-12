/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 16:00:26 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// The routine will follow the sequence of eat > sleep > think.
// However, even-numbered philosophers will start out sleeping.
// The staggered schedules will help to prevent a deadlock situation
// when picking up the forks.
// Once a philosopher has eaten all his meals, his thread will be
// terminated by breaking out of the loop and ending his routine.
void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_monitor;

	philo = (t_philo *) arg;
	if (pthread_create(&death_monitor, NULL, check_philo_death, philo))
		return ("Thread create error");
	pthread_detach(death_monitor);
	if (philo->id % 2 == 0)
	{
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	while (!(any_philo_dead(philo) && !(all_philos_full(philo))))
	{
		philo_eats(philo);
		if (increment_full_philos(philo))
			break ;
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}

// The philosopher will attempt to take both forks.
// If he succesfully takes the left fork but fails
// to take the right fork, the left fork will be relinquished
// to avoid a deadlock situation.
// Once he is successful in taking the forks, the forks taken and
// eating message will be printed for him.
// His last meal timestamp will be updated and his meals eaten
// count will be incremented.
// The thread will then sleep for the specified eating time.
// Once the thread awakes, the fork mutexes will be unlocked
// to allow the next philosopher to pick up the forks.
void	philo_eats(t_philo *philo)
{
	if (pthread_mutex_lock(philo->left_fork) == 0)
	{
		if (pthread_mutex_lock(philo->right_fork) == 0)
		{
			print(philo, TAKEN_FORK);
			print(philo, TAKEN_FORK);
			print(philo, EAT);
			philo->last_meal = timestamp();
			philo->meals_eaten++;
			ft_usleep(philo->data->time_to_eat);
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		else
			pthread_mutex_unlock(philo->left_fork);
	}
}

// The sleeping message will be printed for the philosopher.
// The thread will then sleep for the specified sleeping time.
void	philo_sleeps(t_philo *philo)
{
	print(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
}

// The thinking message will be printed for the philosopher.
// Since thinking time is not specified to the program,
// only the message will be printed.
void	philo_thinks(t_philo *philo)
{
	print(philo, THINK);
}
