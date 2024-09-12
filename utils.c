/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:42 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 13:01:17 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function prints out the status message for a given philosopher.
// It will include the timestamp, philo id and activity message.
// It has to be locked behind a mutex to prevent race conditions
// if multiple threads try to call printf at the same time.
void	print(t_philo *philo, char *msg)
{
	long	current_time;

	if
	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = timestamp();
	printf("%ld %i %s", timestamp() - philo->data->start_time, philo->id, msg);
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


