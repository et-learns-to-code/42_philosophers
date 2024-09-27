/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:33:53 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 11:24:39 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This is the main function of the program.
// It will first check for incorrect arguments.
// If there are incorrect arguments, it will print the
// correct usage and return -1.
// Keep in mind that the subject prohibits use of the exit
// function for the mandatory part.
// The data and philo structs will be initialized and the
// simulation will be run.
// After the simulation terminates, all the previously malloc'd
// data will be freed and the initialized mutexes destroyed.
int	main(int ac, char **av)
{
	t_data	*data;

	if (incorrect_args(ac, av))
		return (correct_usage(), -1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (-1);
	data_init(data, av);
	philo_init(data);
	run_simulation(data);
	clean_up(data);
	return (0);
}

// The clean up function will be called in the parent process
// but also every single child process before it exits.
// This is because each child process will duplicate the malloc'd
// data and the named semaphores. Strictly speaking, the malloc'd
// data is copied-on-write, meaning that the child duplicates the
// memory only if it modifies its contents. For our purposes, the
// memory is duplicated because each philosopher updates its own
// meal variables.
void	clean_up(t_data *data)
{
	free(data->philos);
	sem_close(data->forks_sem);
	sem_close(data->print_sem);
	sem_close(data->meal_sem);
	sem_close(data->eaten_sem);
	unlink_semaphores();
	free(data);
}
