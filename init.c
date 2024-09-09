/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:35 by etien             #+#    #+#             */
/*   Updated: 2024/09/09 18:36:46 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function will initiate the variables in the data struct
// by drawing from the command line arguments.
// Only the philosophers struct will be malloced.
int data_init(t_data *data, char **av)
{
	data->nbr_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nbr_meals = ft_atol(av[5]);
	data->philos = malloc(data->nbr_philos * sizeof(t_philo));
	if (!data->philos)
		return (MALLOC_ERR);
	pthread_mutex_init(&data->print, NULL);
	return (0);
}

// This function will initiate the variables in all the philo structs.
// Assignment of forks will be such that each philosopher's right fork
// is the left fork of the philosopher after him.
// Only the last philosopher's right fork is the left fork of the first
// philosopher in order to simulate a circular seating arrangement.
void philo_init(t_data *data);
{
	int i;

	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = 0;
		pthread_mutex_init(&data->philos[i]->left_fork, NULL);
		if (i == data->nbr_philos - 1)
			data->philos[i].right_fork = data->philos[1].left_fork
		else
			data->philos[i].right_fork = data->philos[i + 1].left_fork;
		i++;
	}
	run_simulation(data);
}

// This function will create the threads for each philosopher and monitor.
// It will also rejoin the threads back with the main thread.
void	run_simulation(t_data *data)
{
	int i;

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
		if (pthread_join(&data->philos[i].thread, NULL))
			return THREAD_JOIN_ERR;
		i++;
	}

}


void *philo_routine(void *args)
{


}
