/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:36:06 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 16:19:32 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function is run by the death monitor thread.
// In the beginning, the thread will sleep until it is close to time_to_die.
// Once awake, it runs a loop of periodically checking for death status
// then sleeping for 2ms to conserve CPU resources.
// When the death condition is detected, the death status is printed and
// exit(1) is called, which will terminate the child process along with
// its death monitor thread.
// The subject states that a philosopher's death has to be reported within 10ms.
// The print semaphore is not increased again with sem_post because the
// death status should be the last statement printed by the program.
// This will prevent the death of other philosophers from being announced.
void	*check_philo_death(void *arg)
{
	t_philo			*philo;
	int				time_to_die;
	struct timeval	tv;
	long long		timestamp;

	philo = (t_philo *)arg;
	time_to_die = philo->data->time_to_die;
	ft_usleep(time_to_die);
	while (1)
	{
		gettimeofday(&tv, NULL);
		timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		if (timestamp - philo->last_meal > time_to_die)
		{
			sem_wait(philo->data->print_sem);
			printf("%lld %i %s", timestamp - philo->data->start_time,
				philo->id, DIED);
			exit(1);
		}
		ft_usleep(2);
	}
	return (NULL);
}
