/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/17 00:05:55 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*ft_philo_init(t_args args, t_lock *lock)
{
	t_philo	*philo;
	size_t	i;

	philo = malloc(args.number_of_philosophers * sizeof(t_philo));
	if (!philo)
		return (ft_pstderr(__ERR_4), NULL);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].state = thinking;
		philo[i].simulation = &lock[args.number_of_philosophers];
		philo[i].number = i + 1;
		philo[i].left_fork = &lock[i];
		philo[i].right_fork = NULL;
		if (args.number_of_philosophers > 1)
			philo[i].right_fork = &lock[(i + 1) % args.number_of_philosophers];
		philo[i].time_to_die = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_to_sleep = args.time_to_sleep;
		philo[i].number_of_times_must_eat
			= args.number_of_times_each_philosopher_must_eat;
		++i;
	}
	return (philo);
}

static void	ft_philo_detach(t_philo *philo, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_detach(philo[i].id);
		++i;
	}
}

static uint8_t	ft_philo_create(t_philo *philo, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_routine, &philo[i]))
			return (ft_philo_detach(philo, i), ft_pstderr(__ERR_6), 0);
		++i;
	}
	return (1);
}

static void	ft_philo_join(t_philo *philo, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_join(philo[i].id, NULL);
		++i;
	}
}

uint8_t	ft_simulate(t_args args)
{
	t_lock	*lock;
	t_philo	*philo;

	if (!args.number_of_philosophers)
		return (1);
	lock = ft_lock_init(args.number_of_philosophers + 1);
	if (!lock)
		return (0);
	philo = ft_philo_init(args, lock);
	if (!philo)
		return (ft_lock_free(lock, args.number_of_philosophers), 0);
	ft_lock_acquire(&lock[args.number_of_philosophers]);
	if (!ft_philo_create(philo, args.number_of_philosophers))
		return (ft_lock_free(lock, args.number_of_philosophers), \
			free(philo), 0);
	ft_lock_release(&lock[args.number_of_philosophers]);
	ft_philo_join(philo, args.number_of_philosophers);
	ft_lock_free(lock, args.number_of_philosophers);
	free(philo);
	return (1);
}
