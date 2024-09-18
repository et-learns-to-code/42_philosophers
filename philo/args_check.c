/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etien <etien@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:08:24 by etien             #+#    #+#             */
/*   Updated: 2024/09/17 11:40:55 by etien            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// This function will print out the correct usage for the program.
void	correct_usage(void)
{
	printf("Correct usage:\n");
	printf("./philo number_of_philosophers ");
	printf("time_to_die time_to_eat time_to_sleep\n");
	printf("[number_of_times_each_philosopher_must_eat]\n");
	printf("1) All arguments must be positive numbers.\n");
	printf("2) number_of_philosophers must be between 1 and 200.\n");
	printf("3) time_to_die, time_to_eat and time_to_sleep must be \
at least 60ms.\n");
	printf("4) [number_of_times_each_philosopher_must_eat] must be greater \
than 0.\n");
}

// This function will check the arguments to the program.
// The program can accept 4 (ac = 5) or 5 (ac = 6) arguments only.
// The arguments must constitute digits and have values that fall
// within the acceptable range.
bool	incorrect_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (true);
	if (args_not_digits(av))
		return (true);
	if (invalid_args(av))
		return (true);
	return (false);
}

// This function will return true if any of the arguments are not
// composed entirely of digits.
// i starts from 1 to skip over the program name (av[0]).
bool	args_not_digits(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

// This function checks that the argument values are valid:
// av[1] number_of_philosophers: 1 to 200 only
// av[2] time_to_die >= 60ms
// av[3] time_to_eat >= 60ms
// av[4] time_to_sleep >= 60ms
// av[5] [number_of_times_each_philosopher_must_eat] > 0
// av[5] is an optional argument, so we have to check for its
// existence first before accessing it to avoid segmentation fault.
// The function will return true if any of the arguments are invalid.
bool	invalid_args(char **av)
{
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return (true);
	if (ft_atoi(av[2]) < 60
		|| ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) < 60)
		return (true);
	if (av[5])
		if (ft_atoi(av[5]) == 0)
			return (true);
	return (false);
}
