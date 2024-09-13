/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:40:00 by etien             #+#    #+#             */
/*   Updated: 2024/09/13 15:45:52 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// The death monitor thread is created at the start and rejoined
// once the philosopher has ended his routine.
// The routine will follow the sequence of eat > sleep > think.
// At the start, even-numbered philosophers will be slightly delayed
// by calling ft_usleep for 10 milliseconds.
// This will minimize contention for picking up the forks during
// the first round of eating. From then on, the philosophers will
// have staggered schedules which will reduce the chances for deadlock.
// A special check will sleep and terminate the routine if there is only
// one philosopher since he has only one fork and will be unable to eat.
// Once a philosopher is full (checked by philo_eats_and_check_full),
// he will end his routine. The philosopher will only repeat his routine so
// long as the shared dead_philo flag has not been marked as true.
void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_monitor;

	philo = (t_philo *) arg;
	if (pthread_create(&death_monitor, NULL, check_philo_death, philo))
		return ("Thread create error");
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!(any_philo_dead(philo)))
	{
		if (philo->data->nbr_philos == 1)
		{
			ft_usleep(philo->data->time_to_die);
			break ;
		}
		if (philo_eats_and_check_full(philo))
			break ;
		philo_sleeps(philo);
		philo_thinks(philo);
	}
	if (pthread_join(death_monitor, NULL))
		return ("Thread join error");
	return (NULL);
}

// The philosopher will attempt to take both forks.
// If he succesfully takes the left fork but fails to take the
// right fork, the left fork will be relinquished to avoid a deadlock situation.
// Once he is successful in taking the forks, the forks taken and
// eating message will be printed for him.
// The thread will then sleep for the specified eating time.
// Once the thread awakes, the meal mutex will be locked and the philosopher's
// last meal timestamp and meals eaten count will be updated.
// The meal and fork mutexes will then be unlocked to allow the next philosopher
// to pick up the forks. Finally, a boolean will be returned to indicate
// whether the philosopher is full after eating his meal.
bool	philo_eats_and_check_full(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print(philo, TAKEN_FORK);
	print(philo, TAKEN_FORK);
	print(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (philo_is_full(philo));
}

// This function will check whether the philosopher is full
// by accessing the meals_eaten variable through the meal mutex.
bool	philo_is_full(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->meals_eaten == philo->data->nbr_meals)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (false);
}

// The sleeping message will be printed for the philosopher.
// The thread will then sleep for the specified sleeping time.
void	philo_sleeps(t_philo *philo)
{
	print(philo, SLEEP);
	ft_usleep(philo->data->time_to_sleep);
}

// The thinking message will be printed for the philosopher.
// Since thinking time is not specified to the program,
// only the message will be printed.
void	philo_thinks(t_philo *philo)
{
	print(philo, THINK);
}
