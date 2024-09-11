/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:36:06 by etien             #+#    #+#             */
/*   Updated: 2024/09/11 12:47:47 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_philo_death(void *arg)
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
			update_death(philo);
			break;
		}
		ft_usleep(2000);
	}
	return (NULL);
}

void update_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	philo->data->dead_philo = true;
	print(philo, DIED);
	pthread_mutex_unlock(&philo->data->death_mutex);
}
