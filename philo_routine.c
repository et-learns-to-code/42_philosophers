/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/10 12:00:55 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *philo_dead(void *arg)
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
		elapsed_time = current_time - philo->last_meal
		if (elapsed_time > time_to die)
		{




	}


}


void update_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data.death_mutex);
	philo->data.dead_philo = true;
	print(philo, DIED);
	pthread_mutex_unlock(&philo->data.death_mutex);
}


void *philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_monitor;

	philo = (t_philo *) arg;
	if (pthread_create(&death_monitor, NULL, philo_dead, philo))
		return THREAD_CREATE_ERR;
	pthread_detach(&death_monitor);



	philo_takes_forks(philo);
	philo_eats(philo);


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
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&philo->right_fork);

}


