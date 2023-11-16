/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:49:22 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/16 21:49:47 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_lock_free(t_lock *lock, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_mutex_destroy(&lock[i].mutex);
		++i;
	}
	free(lock);
}
