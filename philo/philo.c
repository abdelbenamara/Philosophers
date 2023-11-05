/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:58 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/05 22:47:08 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	*args;

	if (ac < 5 || ac > 6)
		return (ft_pstderr(USAGE), 2);
	args = ft_init_args(av + 1);
	if (!args)
		return (1);
	printf(DEBUG "number_of_philosophers: %ld\n", args->number_of_philosophers);
	printf(DEBUG "time_to_die (ms): %ld\n", args->time_to_die);
	printf(DEBUG "time_to_eat (ms): %ld\n", args->time_to_eat);
	printf(DEBUG "time_to_sleep (ms): %ld\n", args->time_to_sleep);
	if (args->number_of_times_each_philosopher_must_eat)
		printf(DEBUG "number_of_times_each_philosopher_must_eat: %ld\n", \
			*(args->number_of_times_each_philosopher_must_eat));
	else
		printf(DEBUG "number_of_times_each_philosopher_must_eat: %p\n", \
			args->number_of_times_each_philosopher_must_eat);
	ft_clear_args(args);
	return (0);
}
