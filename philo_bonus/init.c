/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:35 by etien             #+#    #+#             */
/*   Updated: 2024/09/21 16:15:47 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function will initialize the variables in the data struct
// by drawing from the command line arguments.
// The forks, print and death semaphores are necessary to synchronize
// shared resources and communicate across multiple philosopher processes.
// The meal semaphore functions more like a local mutex to synchronize
// access between the death monitoring thread and the philosopher child
// process to their shared meal variables.
// Only the death semaphore is designed to be locked from the start.
// sem_open requires a semaphore name to enable communication between
// different processes becauses processes do not share the same
// memory space.
// 0644 permissions enables read and write for owner while others can
// only read - often the default setting to protect shared resources.
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
	if (malloc_philos(data))
		return (-1);
	data->forks_sem = sem_open("/forks", O_CREAT, 0644, data->nbr_philos);
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	data->meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
	data->death_sem = sem_open("/death", O_CREAT, 0644, 0);
	return (0);
}

// The philosopher structs have to be malloc'd because
// the number of philosophers is only known at runtime.
int	malloc_philos(t_data *data)
{
	int	n;

	n = data->nbr_philos;
	data->philos = malloc(n * sizeof(t_philo));
	if (!data->philos)
		return (-1);
	return (0);
}

// This function will initialize the variables in all the philo structs.
// last_meal will be initialized to synchronize with the simulation
// start time in the run_simulation function.
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
		i++;
	}
}
