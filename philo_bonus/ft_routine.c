/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:42:35 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/28 08:18:57 by abenamar         ###   ########.fr       */
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

static void	*ft_time_to_die_routine(void *arg)
{
	t_philo	*philo;
	uint8_t	watch;

	philo = (t_philo *) arg;
	watch = 1;
	while (watch)
	{
		sem_wait(philo->run);
		if (philo->state == thinking)
		{
			if (ft_timestamp(philo->start) >= philo->time_to_die)
			{
				printf("%ld %ld died\n", \
					ft_timestamp(philo->global_start), philo->number);
				sem_post(philo->abort);
				watch = 0;
			}
		}
		else
			watch = 0;
		sem_post(philo->run);
		usleep(1);
	}
	return (NULL);
}

static void	ft_philo_eat(t_philo *philo, size_t number, struct timeval start)
{
	pthread_t	id;

	philo[number].global_start = start;
	if (pthread_create(&id, NULL, &ft_time_to_die_routine, &philo[number]))
	{
		ft_pstderr(__ERR_7);
		sem_post(philo[number].abort);
	}
	pthread_detach(id);
	sem_wait(philo[number].forks);
	printf("%ld %ld has taken a fork\n", ft_timestamp(start), number + 1);
	sem_wait(philo[number].forks);
	printf("%ld %ld has taken a fork\n", ft_timestamp(start), number + 1);
	sem_wait(philo[number].run);
	gettimeofday(&philo[number].start, NULL);
	philo[number].state = eating;
	printf("%ld %ld is eating\n", ft_timestamp(start), number + 1);
	if (philo[number].number_of_times_must_eat)
		++philo[number].meal_count;
	sem_post(philo[number].run);
}

static void
	ft_philo_sleep_or_think(t_philo *philo, size_t number, struct timeval start)
{
	if (philo[number].state == eating)
	{
		if (ft_timestamp(philo[number].start) >= philo[number].time_to_eat)
		{
			sem_post(philo[number].forks);
			sem_post(philo[number].forks);
			philo[number].state = sleeping;
			printf("%ld %ld is sleeping\n", ft_timestamp(start), number + 1);
			if (philo[number].number_of_times_must_eat
				&& philo[number].meal_count
				== *philo[number].number_of_times_must_eat)
				sem_post(philo[number].meal_goals);
		}
	}
	else
	{
		if (ft_timestamp(philo[number].start)
			>= philo[number].time_to_eat + philo[number].time_to_sleep)
		{
			philo[number].state = thinking;
			printf("%ld %ld is thinking\n", ft_timestamp(start), number + 1);
		}
	}
}

void	ft_routine(t_philo *philo, size_t number, sem_t **sem)
{
	struct timeval	start;

	sem_wait(philo[number].forks);
	sem_post(philo[number].forks);
	gettimeofday(&start, NULL);
	gettimeofday(&philo[number].start, NULL);
	printf("%ld %ld is thinking\n", ft_timestamp(start), number + 1);
	while (ft_timestamp(philo[number].start) < philo[number].time_to_die)
	{
		if (philo[number].state == thinking)
			ft_philo_eat(philo, number, start);
		else
			ft_philo_sleep_or_think(philo, number, start);
		usleep(1);
	}
	if (ft_timestamp(philo[number].start) >= philo[number].time_to_die)
		printf("%ld %ld died\n", ft_timestamp(start), number + 1);
	sem_post(philo[number].abort);
	ft_sem_free(sem);
	free(philo[number].number_of_times_must_eat);
	free(philo);
	exit(EXIT_SUCCESS);
}
