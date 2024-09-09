/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:32:35 by etien             #+#    #+#             */
/*   Updated: 2024/09/09 15:46:09 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int data_init(t_data *data, char **av)
{
	data->nbr_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->nbr_meals = ft_atol(av[5]);
	data->philos = malloc(data->nbr_philos * sizeof(t_philo));
	if (!data->philos)
		return (MALLOC_ERR);
	return (0);

}

void philo_init(t_data *data);

{


}
