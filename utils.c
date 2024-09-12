/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:42 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 14:45:09 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function prints out the status message for a given philosopher.
// It will include the timestamp, philo id and activity message.
// It has to be locked behind a mutex to prevent race conditions
// if multiple threads try to call printf at the same time.
// The function will check for simulation end conditions before printing
// so that all printing ceases once a philosopher has died or
// all philosophers are full.
void	print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!(any_philo_dead(philo) && !(all_philos_full(philo))))
	{
		printf("%ld %i %s", timestamp() - philo->data->start_time,
			philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

// This function converts the ASCII numbers to their long values.
// Long is used to avoid integer overflow.
int	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (sign * result);
}
