/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:36:06 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 10:35:44 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function is run by the death monitor detached thread.
// If a philosopher has died, its corresponding death monitor will
// set the shared dead_philo flag to true.
// It will check the death status and then sleep for 2ms to conserve
// CPU resources. According to the subject, a philosopher's death has
// to be reported within 10ms.
void	*check_philo_death(void *arg)
{
	t_philo		*philo;
	long		time_to_die;
	long		current_time;
	long		elapsed_time;

	philo = (t_philo *) arg;
	time_to_die = philo->data->time_to_die;
	while (1)
	{
		current_time = timestamp();
		elapsed_time = current_time - philo->last_meal;
		if (elapsed_time > time_to_die)
		{
			set_philo_dead(philo);
			break ;
		}
		ft_usleep(2);
	}
	return (NULL);
}

// This function will set the dead_philo boolean to true.
// It is protected behind the death mutex.
// Whenever multiple threads have access to the same shared
// variable, getting and setting functions for that variable
// have to be locked behind a mutex to make it thread-safe.
void	set_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->dead_philo = true;
	print(philo, DIED);
	pthread_mutex_unlock(&philo->data->death_mutex);
}

// This function will check the dead_philo boolean to decide
// whether to continue the philosopher's routine or to terminate
// the thread. It is protected behind the death mutex.
bool	any_philo_dead(t_philo *philo)
{
	bool	dead;

	pthread_mutex_lock(&philo->data->death_mutex);
	dead = philo->data->dead_philo;
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (dead);
}

// This function will increment the full_philos count.
// It is protected behind the full mutex.
bool	increment_full_philos(t_philo *philo)
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

// This function will check the full_philos count to decide
// whether to continue the philosopher's routine or to terminate
// the thread. It is protected behind the full mutex.
bool	all_philos_full(t_philo *philo)
{
	bool	all_full;

	pthread_mutex_lock(&philo->data->full_mutex);
	all_full = (philo->data->full_philos == philo->data->nbr_philos);
	pthread_mutex_unlock(&philo->data->full_mutex);
	return (all_full);
}
