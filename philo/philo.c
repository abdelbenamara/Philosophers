/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:58 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/09 00:46:20 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
		return (ft_pstderr(__USAGE), 2);
	if (!ft_init_args(&args, av + 1))
		return (EXIT_FAILURE);
	printf(__DEBUG "number_of_philosophers: %ld\n",
		args.number_of_philosophers);
	printf(__DEBUG "time_to_die (ms): %ld\n", args.time_to_die);
	printf(__DEBUG "time_to_eat (ms): %ld\n", args.time_to_eat);
	printf(__DEBUG "time_to_sleep (ms): %ld\n", args.time_to_sleep);
	if (args.number_of_times_each_philosopher_must_eat)
		printf(__DEBUG "number_of_times_each_philosopher_must_eat: %ld\n",
			*(args.number_of_times_each_philosopher_must_eat));
	else
		printf(__DEBUG "number_of_times_each_philosopher_must_eat: %p\n",
			args.number_of_times_each_philosopher_must_eat);
	if (!ft_simulate(args))
		return (free(args.number_of_times_each_philosopher_must_eat), \
			EXIT_FAILURE);
	free(args.number_of_times_each_philosopher_must_eat);
	return (EXIT_SUCCESS);
}
