/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:42 by etien             #+#    #+#             */
/*   Updated: 2024/09/18 14:14:40 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// This function prints out the status message for a given philosopher.
// It will include the timestamp, philo id and activity message.
// It is protected behind a
// The function will check for simulation end conditions before printing
// so that all printing ceases once a philosopher has died.
void	print(t_philo *philo, char *msg)
{
	sem_wait(philo->data->print_sem);
	if (!any_philo_dead(philo))
		printf("%lld %i %s", timestamp() - philo->data->start_time,
			philo->id, msg);
	sem_post(philo->data->print_sem);
}

// This function converts the ASCII numbers to their integer values.
int	ft_atoi(const char *str)
{
	int		result;
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
