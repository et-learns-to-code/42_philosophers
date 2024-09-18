/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:19:05 by etien             #+#    #+#             */
/*   Updated: 2024/09/18 11:10:15 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// The philosopher will attempt to take both forks.
// Depending on whether philo id is odd or even, the philosophers
// will lock the forks in different orders in order to avoid deadlock.
// After the philosopher is done eating, the fork mutexes
// will be unlocked to allow the next philosopher to pick up the forks.
// Finally, a boolean will be returned to indicate
// whether the philosopher is full after having his meal.
bool	philo_eats_and_check_full(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	philo_is_eating(philo);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (philo_is_full(philo));
}

// Once the philosopher is successful in taking the forks,
// the forks taken and eating message will be printed for him.
// The meal mutex will be locked and the philosopher's last meal timestamp
// and meals eaten count will be updated. The meal mutex will be unlocked.
// The thread will then sleep for the specified eating time.
// In the subject, time_to_die is measured from the "beginning of their
// last meal", so last_meal timestamp is updated before making
// the thread sleep.
void	philo_is_eating(t_philo *philo)
{
	print(philo, TAKEN_FORK);
	print(philo, TAKEN_FORK);
	print(philo, EAT);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
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
