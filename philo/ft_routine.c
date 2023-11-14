/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:42:35 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/14 10:22:55 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_timestamp(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 
		+ (now.tv_usec - start.tv_usec) / 1000);
}

static uint8_t	ft_lock_acquire(t_lock *lock)
{
	uint8_t	acquired;

	acquired = 0;
	pthread_mutex_lock(&lock->mutex);
	if (lock->available)
	{
		lock->available = 0;
		acquired = 1;
	}
	pthread_mutex_unlock(&lock->mutex);
	return (acquired);
}

static void	ft_lock_release(t_lock *lock)
{
	pthread_mutex_lock(&lock->mutex);
	lock->available = 1;
	pthread_mutex_unlock(&lock->mutex);
}

static void	ft_eat_or_sleep(t_philo *philo, struct timeval start)
{
	uint8_t	forks;

	if (philo->state == thinking)
	{
		forks = ft_lock_acquire(philo->left_fork);
		if (forks == 1 && philo->right_fork)
		{
			forks += ft_lock_acquire(philo->right_fork);
			if (forks == 2)
			{
				gettimeofday(&philo->start, NULL);
				philo->state = eating;
				printf("%ld %ld is eating\n", \
					ft_timestamp(start), philo->number);
			}
		}
		else
			ft_lock_release(philo->left_fork);
	}
	else if (ft_timestamp(philo->start) >= philo->time_to_eat)
	{
		(ft_lock_release(philo->left_fork), ft_lock_release(philo->right_fork));
		philo->state = sleeping;
		printf("%ld %ld is sleeping\n", ft_timestamp(start), philo->number);
	}
}

void	*ft_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *) arg;
	gettimeofday(&start, NULL);
	gettimeofday(&philo->start, NULL);
	printf("%ld %ld is thinking\n", ft_timestamp(start), philo->number);
	while (ft_timestamp(philo->start) < philo->time_to_die)
	{
		if (philo->state == thinking || philo->state == eating)
			ft_eat_or_sleep(philo, start);
		else if (philo->state == sleeping && ft_timestamp(philo->start) >= 
			philo->time_to_eat + philo->time_to_sleep)
		{
			philo->state = thinking;
			printf("%ld %ld is thinking\n", ft_timestamp(start), philo->number);
		}
		pthread_mutex_lock(&philo->simulation->mutex);
		if (!philo->simulation->available)
			philo->time_to_die = 0;
		pthread_mutex_unlock(&philo->simulation->mutex);
	}
	if (ft_lock_acquire(philo->simulation))
		printf("%ld %ld died\n", ft_timestamp(start), philo->number);
	return (EXIT_SUCCESS);
}
