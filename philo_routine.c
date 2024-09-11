/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/11 12:48:29 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function
// The routine will follow the sequence of sleep > think > eat.
// However, even-numbered philosophers will start out sleeping.
// The staggered schedules will help to prevent a deadlock situation
// when picking up the forks.
// Once a philosopher has eaten all his meals, his thread will be
// terminated by breaking out of the loop and ending his routine.
void *philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_monitor;

	philo = (t_philo *) arg;
	if (pthread_create(&death_monitor, NULL, check_philo_death, philo))
		return THREAD_CREATE_ERR;
	pthread_detach(&death_monitor);
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			ft_usleep(philo->data->time_to_sleep);
			print(philo, SLEEP);
		}
		philo_takes_forks(philo);
		philo_eats(philo);
		if (is_philo_full(philo))
			break;
	}
	return (NULL);
}

void philo_takes_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	print(philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->right_fork);
	print(philo, TAKEN_FORK);
}

void philo_eats(t_philo *philo)
{
	print(philo, EAT);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);
}

bool is_philo_full(t_philo *philo)
{
	if (philo->meals_eaten == philo->data->nbr_meals)
	{
		pthread_mutex_lock(&philo->data->full_mutex);
		print(philo, FULL);
		philo->data->full_philos++;
		pthread_mutex_unlock(&philo->data->full_mutex);
		return (true);
	}
	return (false);
}
