/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:35 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 17:21:28 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function will initialize the variables in the data struct
// by drawing from the command line arguments.
// The start_time variable is initialized in the run_simulation function.
// The forks, meal and print semaphores are necessary to synchronize
// the different philosopher processes.
// sem_open requires a system-wide semaphore name to enable communication
// between processes because they do not share the same memory space.
// The named semaphores have to be cleaned up before the start of every new run
// because they can persist in the system if the program was interrupted.
// Not cleaning up the semaphores will lead to undefined behaviour.
// 0644 permissions enable read and write for owner while others can
// only read. This is often the default setting to protect shared resources.
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
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/meal");
	data->forks_sem = sem_open("/forks", O_CREAT, 0644, data->nbr_philos);
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	data->meal_sem = sem_open("/meal", O_CREAT, 0644, 1);
	return (0);
}

// The philosopher struct array has to be malloc'd because
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
// The last_meal variable will be initialized to the simulation start time
// in the run_simulation function.
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
