/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:48:53 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 13:58:58 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function will facilitate the calling of the gettimeofday function.
// The function will fill in the data in the timeval struct.
// tv.tv_sec = number of seconds elapsed since the Unix epoch
// tv.tv_usec = number of microseconds elapsed since the last second.
// * 1000 and / 1000 are to convert to the microseconds basis
// required by the simulation.
// This function will return the sum of the two variables, thereby
// creating the timestamp.
long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// This function adapts the original usleep function to make the
// sleep duration more acccurate.
// The function will sleep for the majority of the time and fine tune
// the short interval (1 second) before the thread is expected
// to wake. This will minimize the overhead of multiple system calls.
// A sleep duration greater than 1 second is the threshold for the
// long sleep. Keep in mind the parameter given to ft_usleep is in
// milliseconds but usleep takes place by the microseconds.
void	ft_usleep(int ms)
{
	long	start_time;

	start_time = timestamp();
	if (ms > 1000)
		usleep((ms - 1) * 1000);
	while (timestamp() - start_time < ms)
		usleep(100);
}
