/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:33:53 by etien             #+#    #+#             */
/*   Updated: 2024/09/18 11:10:10 by etien            ###   ########.fr       */
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
	free(data);
	return (0);
}

void	clean_up(t_data *data)
{
	int	i;
	int	n;

	i = 0;
	n = data->nbr_philos;
	while (i < n)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philos);
	free(data->forks);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->death_mutex);
}
