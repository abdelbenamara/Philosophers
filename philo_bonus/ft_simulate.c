/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/21 02:09:08 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_philo_setup(t_philo *philo, t_args args)
{
	size_t	i;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].id = -1;
		philo[i].time_to_die = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_to_sleep = args.time_to_sleep;
		philo[i].number_of_times_must_eat
			= args.number_of_times_each_philosopher_must_eat;
		philo[i].meal_count = 0;
		philo[i].state = thinking;
		++i;
	}
}

static uint8_t	ft_fork(t_philo *philo, t_args args, sem_t *forks)
{
	size_t	i;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].id = fork();
		if (philo[i].id == -1)
			return (0);
		if (!philo[i].id)
			return (ft_routine(philo, i, forks), 1);
		++i;
	}
	i = 0;
	while (i < args.number_of_philosophers)
	{
		sem_post(forks);
		++i;
	}
	return (1);
}

static uint8_t	ft_wait(t_philo *philo, t_args args)
{
	size_t	i;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (waitpid(philo[i].id, NULL, WUNTRACED) == -1)
			return (0);
		++i;
	}
	return (1);
}

uint8_t	ft_simulate(t_args args, sem_t *forks)
{
	t_philo	*philo;

	if (!args.number_of_philosophers)
		return (1);
	philo = malloc(args.number_of_philosophers * sizeof(t_philo));
	if (!philo)
		return (ft_pstderr(__ERR_4), 0);
	ft_philo_setup(philo, args);
	if (!ft_fork(philo, args, forks))
		return (free(philo), sem_close(forks), \
			ft_pstderr(__ERR_6), ft_wait(philo, args));
	sem_close(forks);
	if (!ft_wait(philo, args))
		return (free(philo), 0);
	free(philo);
	return (1);
}
