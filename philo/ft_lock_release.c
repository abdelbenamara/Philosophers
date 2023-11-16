/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock_release.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:42:53 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/16 23:54:11 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lock_release(t_lock *lock)
{
	pthread_mutex_lock(&lock->mutex);
	lock->acquired = 0;
	pthread_mutex_unlock(&lock->mutex);
}
