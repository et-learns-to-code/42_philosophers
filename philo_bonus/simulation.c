/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:15:02 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 15:21:26 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function will malloc an array to store the children process pids.
// After that, it will initialize the simulation start time and each
// philosopher's last_meal time (which should be the start of the simulation).
// It will fork a child process for each philosopher.
// Each child process will have its own memory space.
// The sem_wait blocks the function until a child process
// posts the death semaphore.
// It will then signal and wait for the child processes to terminate.
int	run_simulation(t_data *data)
{
	struct timeval	tv;
	long long		timestamp;
	int				i;
	pid_t			*philos_pid;

	philos_pid = malloc(data->nbr_philos * sizeof(pid_t));
	if (!philos_pid)
	{
		clean_up(data);
		exit(-1);
	}
	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->start_time = timestamp;
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
// Each child process created will run its philo_routine function
// and keep track of its own philosopher's data.
// The parent process will keep track of all the children pid returned
// from calling the fork function by storing them in an array.
// If an error occurs while forking the process, the program will exit
// with status -1.
void	fork_philos(t_data *data, int i, pid_t *philos_pid)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		philo_routine(&data->philos[i]);
	else if (pid > 0)
		philos_pid[i] = pid;
	else
	{
		free(philos_pid);
		clean_up(data);
		exit(-1);
	}
}

// This function will wait for one child process to terminate first and
// check its exit code. If the exit code is 1 (meaning a child has died)
// or an error, the parent process will kill all the other children processes
// by sending them the SIGTERM signal. SIGTERM requests a process to terminate
// but allows it to clean up first before exiting.
// If the first child process' error code is 0, this means that the child
// process terminated because the philosopher was full. In this case, the
// parent will wait for the next child to terminate and once again inspect
// its exit code. This will be repeated in a loop until all children have
// been recovered.
// The second while loop is mainly applicable if the kill signal was sent out.
// In that case, the parent process will wait for all children to return
// to avoid the creation of zombie processes.
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
