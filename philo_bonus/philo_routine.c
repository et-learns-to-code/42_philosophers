/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/25 17:12:31 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// The death monitor thread is created at the start and rejoined
// once the philosopher has ended his routine.
// The routine will follow the sequence of eat > sleep > think.
// At the start, even-numbered philosophers will be slightly delayed
// by calling ft_usleep for 10 milliseconds.
// This will minimize contention for picking up the forks during
// the first round of eating. From then on, the philosophers will
// have staggered schedules which will reduce the chances for deadlock.
// A special check will sleep and terminate the routine if there is only
// one philosopher since he will have only one fork and will be unable to eat.
// Once a philosopher is full (checked by philo_eats_and_check_full),
// he will end his routine.
void	*philo_routine(t_philo *philo)
{
	pthread_t	death_monitor;

	if (pthread_create(&death_monitor, NULL, check_philo_death, philo))
		return ((void *)-1);
	if (pthread_detach(death_monitor))
		return ((void *)-1);
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (1)
	{
		if (philo->data->nbr_philos == 1)
		{
			ft_usleep(philo->data->time_to_die);
			break ;
		}
		if (philo_eats_and_check_full(philo))
		{
			clean_up(philo->data);
			exit(0);
		}
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}
