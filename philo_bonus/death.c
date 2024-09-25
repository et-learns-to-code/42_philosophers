/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:36:06 by etien             #+#    #+#             */
/*   Updated: 2024/09/25 13:38:41 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function is run by the death monitor thread.
// If a philosopher has died, its corresponding death monitor will
// post the death semaphore and exit the child process.
// In the beginning, the thread will sleep until it is close to time_to_die.
// Once awake, it runs a loop of periodically checking for death status
// then sleeping for 2ms to conserve CPU resources.
// When the death condition is detected, exit(1) is called, which will
// terminate the child process along with its death monitor thread.
// The subject states that a philosopher's death has to be reported within 10ms.
// The print semaphore is not increased again with sem_post because the
// death announcement should be the last statement printed by the program.
// This will prevent the death of other philosophers from being announced.
void	*check_philo_death(void *arg)
{
	t_philo		*philo;
	int			time_to_die;

	philo = (t_philo *)arg;
	time_to_die = philo->data->time_to_die;
	ft_usleep(time_to_die);
	while (!philo_is_full(philo))
	{
		sem_wait(philo->data->meal_sem);
		if (timestamp() - philo->last_meal > time_to_die)
		{
			sem_post(philo->data->meal_sem);
			sem_wait(philo->data->print_sem);
			printf("%lld %i %s", timestamp() - philo->data->start_time,
				philo->id, DIED);
			exit(1);
		}
		sem_post(philo->data->meal_sem);
		ft_usleep(2);
	}
	return (NULL);
}
