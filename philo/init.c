/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:35 by etien             #+#    #+#             */
/*   Updated: 2024/09/17 18:12:18 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function will initialize the variables in the data struct
// by drawing from the command line arguments.
int	data_init(t_data *data, char **av)
{
	data->nbr_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nbr_meals = ft_atoi(av[5]);
	else
		data->nbr_meals = -1;
	data->dead_philo = false;
	data->stop_simulation = false;
	if (malloc_philos_forks(data))
		return (-1);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	return (0);
}

// The philosopher structs and fork mutexes have to be malloc'd because
// the number of philosophers is only known at runtime.
int	malloc_philos_forks(t_data *data)
{
	int	n;

	n = data->nbr_philos;
	data->philos = malloc(n * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	data->forks = malloc(n * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (-1);
	return (0);
}

// This function will initialize the variables in all the philo structs.
// last_meal will be initialized to synchronize with the simulation
// start time in the run_simulation function.
// Each philosopher's left fork will correspond to his i.
// His right fork will correspond to (i + 1).
// Modulus is used so that the last philosopher's right fork is fork[0]
// to simulate a circular seating arrangement.
void	philo_init(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = data->nbr_philos;
	while (i < n)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % n];
		i++;
	}
}

// This function will initialize the simulation start time and
// each philosopher's last_meal time (which should be the start
// of the simulation).
// It will then create the threads for each philosopher.
// It will also rejoin the threads back with the main thread
// after every thread has terminated.
int	run_simulation(t_data *data)
{
	int	i;
	int	n;

	data->start_time = timestamp();
	i = 0;
	n = data->nbr_philos;
	while (i < n)
	{
		data->philos[i].last_meal = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < n)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (-1);
		i++;
	}
	return (0);
}
