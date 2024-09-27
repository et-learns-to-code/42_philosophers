/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:48:53 by etien             #+#    #+#             */
/*   Updated: 2024/09/27 11:01:17 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function will facilitate the calling of the gettimeofday function.
// gettimeofday will automatically fill in the time data in the
// timeval struct passed in as a parameter to it.
// tv.tv_sec = number of seconds elapsed since the Unix epoch
// tv.tv_usec = number of microseconds elapsed since the last second.
// * 1000 and / 1000 are to convert to the milliseconds basis
// required by the simulation.
// This function will return the sum of the two variables, thereby
// creating the timestamp.
// long long	timestamp(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }

// This function adapts the original usleep function to make the
// sleep duration more precise.
// The function will sleep for the majority of the time and fine tune
// the short interval (1 millisecond) before the thread is expected to wake.
// This will minimize the overhead of multiple system calls.
// A sleep duration greater than 1 second is the threshold for the
// long sleep. Keep in mind the parameter given to ft_usleep is in
// milliseconds but usleep occurs by the microseconds.
void	ft_usleep(int ms)
{
	struct timeval	tv;
	long long		timestamp;
	long long		start_time;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	start_time = timestamp;
	if (ms > 1000)
		usleep((ms - 1) * 1000);
	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	while (timestamp - start_time < ms)
	{
		usleep(100);
		gettimeofday(&tv, NULL);
		timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}
}
