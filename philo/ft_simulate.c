/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/14 09:56:44 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_free_lock(t_lock *lock, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&lock[i].mutex);
		++i;
	}
	free(lock);
}

static t_lock	*ft_init_lock(size_t size)
{
	t_lock	*lock;
	size_t	i;

	lock = malloc(size * sizeof(t_lock));
	if (!lock)
		return (ft_pstderr(__ERR_4), NULL);
	i = 0;
	while (i < size)
	{
		lock[i].available = 1;
		if (pthread_mutex_init(&lock[i].mutex, NULL))
			return (ft_free_lock(lock, i + 1), ft_pstderr(__ERR_5), NULL);
		++i;
	}
	return (lock);
}

static t_philo	*ft_init_philo(t_args args, t_lock *lock)
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
			philo[i].right_fork = &lock[i + 1 % args.number_of_philosophers];
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
	t_lock	*lock;
	t_philo	*philo;
	size_t	i;

	if (!args.number_of_philosophers)
		return (1);
	lock = ft_init_lock(args.number_of_philosophers + 1);
	if (!lock)
		return (0);
	philo = ft_init_philo(args, lock);
	if (!philo)
		return (ft_free_lock(lock, args.number_of_philosophers), 0);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_routine, &philo[i]))
			return (ft_free_lock(lock, args.number_of_philosophers), \
				free(philo), ft_pstderr(__ERR_6), 0);
		++i;
	}
	i = 0;
	while (i < args.number_of_philosophers)
		(pthread_join(philo[i].id, NULL), ++i);
	(ft_free_lock(lock, args.number_of_philosophers), free(philo));
	return (1);
}
