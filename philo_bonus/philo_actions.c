/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:19:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/25 13:40:11 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// The philosopher will attempt to take both forks and decrease
// the forks semaphore.
// After the philosopher is done eating, the forks semaphore will
// be increased to allow the next philosopher to pick up the forks.
// Finally, a boolean will be returned to indicate
// whether the philosopher is full after having his meal.
bool	philo_eats_and_check_full(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	sem_wait(philo->data->forks_sem);
	philo_is_eating(philo);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	return (philo_is_full(philo));
}

// Once the philosopher is successful in taking the forks,
// the forks taken and eating message will be printed for him.
// The meal semaphore will be decreased and the philosopher's last meal
// timestamp and meals eaten count will be updated.
// The meal semaphore will be increased.
// The thread will then sleep for the specified eating time.
// In the subject, time_to_die is measured from the "beginning of their
// last meal", so last_meal timestamp is updated before making
// the thread sleep.
void	philo_is_eating(t_philo *philo)
{
	print(philo, TAKEN_FORK);
	print(philo, TAKEN_FORK);
	print(philo, EAT);
	sem_wait(philo->data->meal_sem);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	sem_post(philo->data->meal_sem);
	ft_usleep(philo->data->time_to_eat);
}

// This function will check whether the philosopher is full
// by accessing the meals_eaten variable through the meal semaphore.
// If the philosopher is full, the full semaphore will be posted.
bool	philo_is_full(t_philo *philo)
{
	sem_wait(philo->data->meal_sem);
	if (philo->meals_eaten == philo->data->nbr_meals)
	{
		sem_post(philo->data->meal_sem);
		return (true);
	}
	sem_post(philo->data->meal_sem);
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
