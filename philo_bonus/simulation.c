/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:15:02 by etien             #+#    #+#             */
/*   Updated: 2024/09/25 17:47:26 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function will initialize the simulation start time and
// each philosopher's last_meal time (which should be the start
// of the simulation).
// It will fork a child process for each philosopher.
// Each child process will have its own memory space.
// The sem_wait blocks the function until a child process
// posts the death semaphore.
// It will then signal and wait for the child processes to terminate.
int	run_simulation(t_data *data)
{
	int			i;
	pid_t		*philos_pid;

	philos_pid = malloc(data->nbr_philos * sizeof(pid_t));
	if (!philos_pid)
		return (-1);
	data->start_time = timestamp();
	i = 0;
	while (i < data->nbr_philos)
	{
		data->philos[i].last_meal = data->start_time;
		fork_philos(data, i, philos_pid);
		i++;
	}
	recover_philos(data, philos_pid);
	free(philos_pid);
	return (0);
}

// This function forks the process for each philosopher.
// The child process created will run the philo_routine function.
// exit(0) is necessary to cleanly terminate the child.
// The parent process will keep track of all the children pid
// with the help of an array.
// If an error occurs, the program will exit with status 1.
void	fork_philos(t_data *data, int i, pid_t *philos_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		philo_routine(&data->philos[i]);
	else if (pid > 0)
		philos_pid[i] = pid;
	else
		exit(-1);
}

// This function will signal for all the child processes to terminate
// with SIGTERM (request a process to terminate but allow it to
// clean up before exiting). After the signal is given, the main
// function will still wait for its children to finish to avoid
// the creation of zombie processes.
// The reason two while loops are used is to prevent delays when
// number of philosophers is high.
void	recover_philos(t_data *data, pid_t *philos_pid)
{
	int	i;
	int	exit_code;

	i = 0;
	while (i < data->nbr_philos)
	{
		waitpid(-1, &exit_code, 0);
		if (exit_code != 0)
		{
			i = 0;
			while (i < data->nbr_philos)
			{
				kill(philos_pid[i], SIGTERM);
				i++;
			}
			break ;
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_philos)
	{
		waitpid(philos_pid[i], NULL, 0);
		i++;
	}
}
