/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lock_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:48:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/22 10:26:17 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_lock	*ft_lock_init(size_t size)
{
	t_lock	*lock;
	size_t	i;

	lock = malloc(size * sizeof(t_lock));
	if (!lock)
		return (ft_pstderr(__ERR_4), NULL);
	i = 0;
	while (i < size)
	{
		lock[i].acquired = 0;
		if (pthread_mutex_init(&lock[i].mutex, NULL))
			return (ft_lock_free(lock, i), ft_pstderr(__ERR_5), NULL);
		++i;
	}
	return (lock);
}
