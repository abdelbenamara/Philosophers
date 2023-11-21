/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:42:35 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/21 02:12:00 by abenamar         ###   ########.fr       */
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

void	ft_routine(t_philo *philo, size_t number, sem_t *forks)
{
	struct timeval	start;

	sem_wait(forks);
	gettimeofday(&start, NULL);
	gettimeofday(&philo[number].start, NULL);
	printf("%ld %ld is thinking\n", ft_timestamp(start), number + 1);
	sem_post(forks);
	free(philo->number_of_times_must_eat);
	free(philo);
	sem_close(forks);
	exit(EXIT_SUCCESS);
}
