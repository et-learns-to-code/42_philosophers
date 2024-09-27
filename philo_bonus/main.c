/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:33:53 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 15:11:11 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This is the main function of the program.
// It will first check for incorrect arguments.
// If there are incorrect arguments, it will print the
// correct usage and exit with status -1.
// The data and philo structs will be initialized and the
// simulation will be run.
// After the simulation terminates, all the previously malloc'd
// data and semaphores will be cleaned up.
int	main(int ac, char **av)
{
	t_data	*data;

	if (incorrect_args(ac, av))
	{
		correct_usage();
		exit(-1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		exit(-1);
	data_init(data, av);
	philo_init(data);
	run_simulation(data);
	clean_up(data);
	exit(0);
}

// The clean up function frees
void	clean_up(t_data *data)
{
	if (data)
	{
		if(data->philos)
			free(data->philos);
		if(data->forks_sem)
			sem_close(data->forks_sem);
		if(data->print_sem)
			sem_close(data->print_sem);
		if(data->meal_sem)
			sem_close(data->meal_sem);
		sem_unlink("/forks");
		sem_unlink("/print");
		sem_unlink("/meal");
		free(data);
	}
}
