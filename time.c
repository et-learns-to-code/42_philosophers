/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:48:53 by etien             #+#    #+#             */
/*   Updated: 2024/09/11 10:33:44 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function will facilitate calling of the gettimeofday function.
// We feed a timeval struct to the function which will fill in the data
// for us.
// tv.tv_sec will be the number of seconds elapsed since the Unix epoch
// tv.tv_usec will be the number of microseconds elapsed since the last
// second.
// *1000 and /1000 are to convert to the microseconds basis required by
// the simulation.
// This function will return the sum of the two variables, thereby
// delivering the timestamp.
long timestamp(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// This function adapts the original usleep function to make the
// sleep duration more acccurate.
// The function will sleep for the majority of the sleep duration and
// then fine tune the short interval (1 second) until the thread is expected
// to wake. This will minimize the overhead of multiple system calls.
// 1 second is used as the threshold for the long sleep.
// Keep in mind the parameter given is in milliseconds but usleep
// takes place by the microseconds.
void ft_usleep(int ms)
{
	long	start_time;

	start_time = timestamp();
	if (ms > 1000)
		usleep((ms - 1) * 1000);
	while (timestamp() - start_time < ms)
		usleep(100);
}


