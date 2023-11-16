/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:58 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/16 22:13:13 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static uint8_t	ft_is_natural_number(const char *nptr)
{
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '+')
		++nptr;
	while (*nptr)
	{
		if (*nptr < '0' || '9' < *nptr)
			break ;
		++nptr;
	}
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr)
		return (0);
	return (1);
}

static uint8_t	ft_arg_setup(size_t *nb, const char *nptr)
{
	size_t	i;
	char	*s;

	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '+')
		++nptr;
	i = ft_atos(nptr);
	s = ft_stoa(i);
	if (!s)
		return (0);
	if (ft_strncmp(s, nptr, ft_strlen(s)))
		return (ft_pstderr(__ERR_2), free(s), 0);
	free(s);
	*nb = i;
	return (1);
}

static uint8_t	ft_args_init(t_args *args, char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		if (!ft_is_natural_number(strs[i]))
			return (ft_pstderr(__ERR_1), 0);
		++i;
	}
	if (!ft_arg_setup(&args->number_of_philosophers, strs[0])
		|| !ft_arg_setup(&args->time_to_die, strs[1])
		|| !ft_arg_setup(&args->time_to_eat, strs[2])
		|| !ft_arg_setup(&args->time_to_sleep, strs[3]))
		return (0);
	if (args->number_of_philosophers > SIZE_MAX / sizeof(t_philo))
		return (ft_pstderr(__ERR_3), 0);
	args->number_of_times_each_philosopher_must_eat = NULL;
	if (!(strs[4]))
		return (1);
	args->number_of_times_each_philosopher_must_eat = malloc(sizeof(size_t));
	if (!(args->number_of_times_each_philosopher_must_eat))
		return (ft_pstderr(__ERR_4), 0);
	if (!ft_arg_setup(args->number_of_times_each_philosopher_must_eat, strs[4]))
		return (free(args->number_of_times_each_philosopher_must_eat), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_args	args;

	if (ac < 5 || ac > 6)
		return (ft_pstderr(__USAGE), 2);
	if (!ft_args_init(&args, av + 1))
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
