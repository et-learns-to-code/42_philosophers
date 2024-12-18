/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 17:50:08 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// The death monitor thread is created at the start of the child process
// and immediately detached. The OS will clean up the resources used by
// the detached thread when the program terminates.
// The philosopher's routine will follow the sequence of eat > sleep > think.
// At the start, even-numbered philosophers will be slightly delayed
// by calling ft_usleep for 10 milliseconds.
// This will minimize contention for picking up the forks during
// the first round of eating. From then on, the philosophers will
// have staggered schedules which will reduce the chances for deadlock.
// If there is only one philosopher, the philosopher will be put into
// an eternal sleep loop until the death monitor terminates it because
// the philosopher will only have one fork and will be unable to eat.
// Once a philosopher is full (checked by philo_eats_and_check_full),
// he will call exit(0) to terminate both himself and his death monitor thread.
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
			while (1)
				ft_usleep(philo->data->time_to_die);
		}
		if (philo_eats_and_check_full(philo))
			exit(0);
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	return (NULL);
}
