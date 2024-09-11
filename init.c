/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:35 by etien             #+#    #+#             */
/*   Updated: 2024/09/11 15:26:16 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function will initiate the variables in the data struct
// by drawing from the command line arguments.
// Only the philosophers struct will be malloced.
void data_init(t_data *data, char **av)
{
	data->nbr_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nbr_meals = ft_atol(av[5]);
	else
		data->nbr_meals = -1;
	data->dead_philo = false;
	data->full_philos = 0;
	malloc_philos_forks(data);
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->full_mutex, NULL);
}

void malloc_philos_forks(t_data *data)
{
	data->philos = malloc(data->nbr_philos * sizeof(t_philo));
	if (!data->philos)
		return (MALLOC_ERR);
	data->forks = malloc(data->nbr_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
	{
		free(data->philos);
		return (MALLOC_ERR);
	}
}

// This function will initiate the variables in all the philo structs.
// Each philosopher's left fork will correspond to its i.
// His right fork will correspond to (i + 1).
// Modulus is used so that the last philosopher's right fork is fork[0]
// to simulate a circular seating arrangement.
void philo_init(t_data *data)
{
	int i;
	int n;

	i = 0;
	n = data->nbr_philos;
	while (i < n)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].meals_eaten = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % n];
		i++;
	}
	run_simulation(data);
}

// This function will create the threads for each philosopher and monitor.
// It will also rejoin the threads back with the main thread.
void	run_simulation(t_data *data)
{
	int i;

	data->start_time = timestamp();
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]))
		// free resources
			return THREAD_CREATE_ERR;
		i++;
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return THREAD_JOIN_ERR;
		i++;
	}
}
