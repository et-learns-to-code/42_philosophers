/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:10:42 by etien             #+#    #+#             */
/*   Updated: 2024/09/12 10:35:12 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, char *msg)
{
	long	current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = timestamp();
	printf("%ld %i %s", timestamp() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
