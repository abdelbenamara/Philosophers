/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:42:35 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/09 02:36:19 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	start;
	struct timeval	end;
	size_t			now;

	philo = (t_philo *) arg;
	gettimeofday(&start, NULL);
	gettimeofday(&end, NULL);
	now = (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_usec - start.tv_usec) / 1000;
	printf("%ld %ld is sleeping\n", now, philo->number);
	while (now < philo->time_to_die)
	{
		gettimeofday(&end, NULL);
		now = (end.tv_sec - start.tv_sec) * 1000
			+ (end.tv_usec - start.tv_usec) / 1000;
	}
	printf("%ld %ld died\n", now, philo->number);
	return (EXIT_SUCCESS);
}
