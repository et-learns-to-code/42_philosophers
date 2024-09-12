/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_simulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:36:06 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 17:52:24 by etien            ###   ########.fr       */
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

	philo = (t_philo *) arg;
	time_to_die = philo->data->time_to_die;
	ft_usleep(time_to_die);
	while (1)
	{
		if (timestamp() - philo->last_meal > time_to_die)
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
	if (!philo->data->stop_simulation)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%ld %i %s", timestamp() - philo->data->start_time,
			philo->id, DIED);
		pthread_mutex_unlock(&philo->data->print_mutex);
		philo->data->stop_simulation = true;
	}
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
