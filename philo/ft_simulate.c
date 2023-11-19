/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/19 11:21:11 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_philo_setup(t_philo *philo, t_args args, t_lock *lock)
{
	size_t	i;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].number = i + 1;
		philo[i].time_to_die = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_to_sleep = args.time_to_sleep;
		philo[i].number_of_times_must_eat
			= args.number_of_times_each_philosopher_must_eat;
		philo[i].meal_count = 0;
		philo[i].state = thinking;
		philo[i].run = &lock[2 * args.number_of_philosophers];
		philo[i].abort = &lock[2 * args.number_of_philosophers + 1];
		philo[i].left_fork = &lock[i];
		philo[i].right_fork = NULL;
		if (args.number_of_philosophers > 1)
			philo[i].right_fork = &lock[(i + 1) % args.number_of_philosophers];
		philo[i].meal_goal = &lock[args.number_of_philosophers + i];
		++i;
	}
}

static uint8_t	ft_philo_create(t_philo *philo, t_args args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		if (pthread_create(&philo[i].id, NULL, &ft_routine, &philo[i]))
		{
			ft_lock_acquire(philo->abort);
			ft_lock_release(philo->run);
			j = 0;
			while (j < i)
			{
				pthread_join(philo[j].id, NULL);
				++j;
			}
			return (0);
		}
		++i;
	}
	return (1);
}

static uint8_t	ft_philo_join(t_philo *philo, t_args args)
{
	uint8_t	result;
	size_t	i;

	result = 1;
	if (args.number_of_times_each_philosopher_must_eat)
	{
		i = 0;
		while (i < args.number_of_philosophers)
		{
			while (!ft_lock_locked(philo[i].run)
				&& !ft_lock_locked(philo[i].meal_goal))
				usleep(1);
			++i;
		}
		ft_lock_acquire(philo->run);
	}
	i = 0;
	while (i < args.number_of_philosophers)
	{
		pthread_join(philo[i].id, NULL);
		++i;
	}
	return (result);
}

uint8_t	ft_simulate(t_args args)
{
	t_lock	*lock;
	t_philo	*philo;

	if (!args.number_of_philosophers)
		return (1);
	lock = ft_lock_init(2 * args.number_of_philosophers + 2);
	if (!lock)
		return (0);
	philo = malloc(args.number_of_philosophers * sizeof(t_philo));
	if (!philo)
		return (ft_lock_free(lock, args.number_of_philosophers + 2), \
			ft_pstderr(__ERR_4), 0);
	ft_philo_setup(philo, args, lock);
	ft_lock_acquire(philo->run);
	if (!ft_philo_create(philo, args))
		return (ft_lock_free(lock, args.number_of_philosophers + 2), \
			free(philo), ft_pstderr(__ERR_6), 0);
	ft_lock_release(philo->run);
	if (!ft_philo_join(philo, args))
		return (ft_lock_free(lock, args.number_of_philosophers + 2), \
			free(philo), 0);
	ft_lock_free(lock, args.number_of_philosophers + 2);
	free(philo);
	return (1);
}
