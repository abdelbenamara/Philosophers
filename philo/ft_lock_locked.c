/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock_locked.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:43:53 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/16 23:54:10 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint8_t	ft_lock_locked(t_lock *lock)
{
	uint8_t	acquired;

	acquired = 0;
	pthread_mutex_lock(&lock->mutex);
	if (lock->acquired)
		acquired = 1;
	pthread_mutex_unlock(&lock->mutex);
	return (acquired);
}
