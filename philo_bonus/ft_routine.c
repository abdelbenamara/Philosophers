/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:42:35 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/22 13:18:49 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static size_t	ft_timestamp(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000 
		+ (now.tv_usec - start.tv_usec) / 1000);
}

static void	ft_philo_eat(t_philo *philo, size_t number, struct timeval start)
{
	sem_wait(philo->forks);
	printf("%ld %ld has taken a fork\n", ft_timestamp(start), number + 1);
	if (ft_timestamp(philo[number].start) >= philo->time_to_die)
		return ;
	sem_wait(philo->forks);
	printf("%ld %ld has taken a fork\n", ft_timestamp(start), number + 1);
	if (ft_timestamp(philo[number].start) >= philo->time_to_die)
		return ;
	gettimeofday(&philo[number].start, NULL);
	philo[number].state = eating;
	printf("%ld %ld is eating\n", ft_timestamp(start), number + 1);
	if (philo->number_of_times_must_eat)
		++philo[number].meal_count;
}

static void	ft_philo_sleep(t_philo *philo, size_t number, struct timeval start)
{
	if (ft_timestamp(philo[number].start) >= philo->time_to_eat)
	{
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo[number].state = sleeping;
		printf("%ld %ld is sleeping\n", ft_timestamp(start), number + 1);
		if (philo->number_of_times_must_eat
			&& philo[number].meal_count == *philo->number_of_times_must_eat)
			sem_post(philo->meal_goal);
	}
}

static void	ft_philo_think(t_philo *philo, size_t number, struct timeval start)
{
	if (ft_timestamp(philo[number].start)
		>= philo->time_to_eat + philo->time_to_sleep)
	{
		philo[number].state = thinking;
		printf("%ld %ld is thinking\n", ft_timestamp(start), number + 1);
	}
}

void	ft_routine(t_philo *philo, size_t number, sem_t **sem)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	gettimeofday(&philo[number].start, NULL);
	printf("%ld %ld is thinking\n", ft_timestamp(start), number + 1);
	while (ft_timestamp(philo[number].start) < philo->time_to_die)
	{
		if (philo[number].state == thinking)
			ft_philo_eat(philo, number, start);
		else if (philo[number].state == eating)
			ft_philo_sleep(philo, number, start);
		else if (philo[number].state == sleeping)
			ft_philo_think(philo, number, start);
		usleep(1);
	}
	sem_post(philo->stop);
	printf("%ld %ld died\n", ft_timestamp(start), number + 1);
	ft_sem_free(sem);
	free(philo->number_of_times_must_eat);
	free(philo);
	exit(EXIT_SUCCESS);
}
