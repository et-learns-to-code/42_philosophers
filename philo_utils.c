/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:42 by etien             #+#    #+#             */
/*   Updated: 2024/09/11 15:18:06 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print(t_philo *philo, char *msg)
{
	long current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = timestamp();
	printf("%ld %i %s", timestamp() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// Philosophers will think in short bursts of time so long
// as they are unable to acquire both forks.
void philo_thinks(t_philo *philo)
{
	ft_usleep(10);
	print(philo, THINK);
}

void philo_sleeps(t_philo *philo)
{
	ft_usleep(philo->data->time_to_sleep);
	print(philo, SLEEP);
}

