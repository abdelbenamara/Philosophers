/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:49:22 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/22 12:45:30 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sem_free(sem_t **sem)
{
	sem_close(sem[0]);
	sem_unlink(__SEM_1);
	sem_close(sem[1]);
	sem_unlink(__SEM_2);
	sem_close(sem[2]);
	sem_unlink(__SEM_3);
	free(sem);
}
