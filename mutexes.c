/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:37:42 by etien             #+#    #+#             */
/*   Updated: 2024/09/09 16:56:35 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print(t_philo *philo, char *msg)
{
	long current_time;

	pthread_mutex_lock(&philo->data->print);
	current_time = timestamp();
	printf("%ld %i %s", timestamp() - philo->data->start_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print);
}

