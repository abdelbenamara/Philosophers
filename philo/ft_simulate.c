/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/09 02:12:02 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*ft_init_philo(t_args args)
{
	t_philo	*philo;
	size_t	i;

	philo = malloc(args.number_of_philosophers * sizeof(t_philo));
	if (!philo)
		return (ft_pstderr(__ERR_4), NULL);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].number = i + 1;
		philo[i].time_to_die = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_to_sleep = args.time_to_sleep;
		philo[i].number_of_times_must_eat
			= args.number_of_times_each_philosopher_must_eat;
		++i;
	}
	return (philo);
}

uint8_t	ft_simulate(t_args args)
{
	t_philo	*philo;
	size_t	i;

	if (!args.number_of_philosophers)
		return (1);
	philo = ft_init_philo(args);
	if (!philo)
		return (0);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_routine, &philo[i]))
			return (ft_pstderr(__ERR_5), free(philo), 0);
		++i;
	}
	i = 0;
	while (i < args.number_of_philosophers)
	{
		pthread_join(philo[i].id, NULL);
		++i;
	}
	free(philo);
	return (1);
}
