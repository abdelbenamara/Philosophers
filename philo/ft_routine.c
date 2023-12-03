/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:42:35 by abenamar          #+#    #+#             */
/*   Updated: 2023/12/03 12:07:56 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_timestamp(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 \
		+ (now.tv_usec - start.tv_usec) / 1000);
}

static void	ft_philo_eat(t_philo *philo, struct timeval start)
{
	uint8_t	forks;

	forks = ft_lock_acquire(philo->left_fork);
	if (forks == 1 && philo->right_fork)
	{
		printf("%ld %ld has taken a fork\n", \
			ft_timestamp(start), philo->number);
		forks += ft_lock_acquire(philo->right_fork);
		if (forks == 2)
		{
			printf("%ld %ld has taken a fork\n", \
				ft_timestamp(start), philo->number);
			gettimeofday(&philo->start, NULL);
			philo->state = eating;
			printf("%ld %ld is eating\n", ft_timestamp(start), philo->number);
			if (philo->number_of_times_must_eat)
				++philo->meal_count;
		}
		else
			ft_lock_release(philo->left_fork);
	}
}

static void	ft_philo_sleep(t_philo *philo, struct timeval start)
{
	if (ft_timestamp(philo->start) >= philo->time_to_eat)
	{
		ft_lock_release(philo->left_fork);
		ft_lock_release(philo->right_fork);
		philo->state = sleeping;
		printf("%ld %ld is sleeping\n", ft_timestamp(start), philo->number);
		if (philo->number_of_times_must_eat
			&& philo->meal_count == *philo->number_of_times_must_eat)
			ft_lock_acquire(philo->meal_goal);
	}
}

static void	ft_philo_think(t_philo *philo, struct timeval start)
{
	if (ft_timestamp(philo->start) >= philo->time_to_eat + philo->time_to_sleep)
	{
		philo->state = thinking;
		printf("%ld %ld is thinking\n", ft_timestamp(start), philo->number);
	}
}

void	*ft_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	start;

	philo = (t_philo *) arg;
	while (ft_lock_locked(philo->run))
		usleep(1);
	if (ft_lock_locked(philo->abort))
		return (NULL);
	gettimeofday(&start, NULL);
	gettimeofday(&philo->start, NULL);
	printf("%ld %ld is thinking\n", ft_timestamp(start), philo->number);
	while (!ft_lock_locked(philo->run)
		&& ft_timestamp(philo->start) < philo->time_to_die)
	{
		if (philo->state == thinking)
			ft_philo_eat(philo, start);
		else if (philo->state == eating)
			ft_philo_sleep(philo, start);
		else if (philo->state == sleeping)
			ft_philo_think(philo, start);
		usleep(1);
	}
	if (ft_timestamp(philo->start) >= philo->time_to_die)
		printf("%ld %ld died\n", ft_timestamp(start), philo->number);
	return (ft_lock_acquire(philo->run), NULL);
}
