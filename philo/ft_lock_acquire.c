/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock_acquire.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:41:44 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/16 23:54:09 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint8_t	ft_lock_acquire(t_lock *lock)
{
	uint8_t	acquired;

	acquired = 0;
	pthread_mutex_lock(&lock->mutex);
	if (!lock->acquired)
	{
		lock->acquired = 1;
		acquired = 1;
	}
	pthread_mutex_unlock(&lock->mutex);
	return (acquired);
}
