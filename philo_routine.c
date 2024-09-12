/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 10:34:53 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// The routine will follow the sequence of sleep > think > eat.
// Thinking is the flexible part of the routine that will only
// take place when a philosopher has to wait for the forks to be
// available.
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
		return (THREAD_CREATE_ERR);
	pthread_detach(&death_monitor);
	if (philo->id % 2 == 0)
		philo_sleeps(philo);
	while (!(any_philo_dead(philo) && !(all_philos_full(philo))))
	{
		philo_takes_forks(philo);
		philo_eats(philo);
		if (increment_full_philos(philo))
			break ;
		philo_sleeps(philo);
	}
	return (NULL);
}

// The philosopher will attempt to lock the right fork.
// If it is still occupied, he will reqlinquish both forks
// and spend the time thinking instead.
void	philo_takes_forks(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		if (pthread_mutex_lock(&philo->right_fork) == 0)
		{
			print(philo, TAKEN_FORK);
			print(philo, TAKEN_FORK);
			return ;
		}
		pthread_mutex_unlock(&philo->left_fork);
		philo_thinks(philo);
	}
}

void	philo_eats(t_philo *philo)
{
	print(philo, EAT);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

void	philo_sleeps(t_philo *philo)
{
	ft_usleep(philo->data->time_to_sleep);
	print(philo, SLEEP);
}

// Philosophers will think in short bursts of time so long
// as they are unable to acquire both forks.
void	philo_thinks(t_philo *philo)
{
	ft_usleep(10);
	print(philo, THINK);
}
