/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:48:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/22 12:45:52 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	**ft_sem_init(void)
{
	sem_t	**sem;

	sem = malloc(3 * sizeof(sem_t *));
	if (!sem)
		return (ft_pstderr(__ERR_4), NULL);
	sem[0] = sem_open(__SEM_1, O_RDWR | O_CREAT | O_EXCL, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 0);
	if (sem[0] == SEM_FAILED)
		return (ft_sem_free(sem), ft_pstderr(__ERR_5), NULL);
	sem[1] = sem_open(__SEM_2, O_RDWR | O_CREAT | O_EXCL, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 0);
	if (sem[1] == SEM_FAILED)
		return (ft_sem_free(sem), ft_pstderr(__ERR_5), NULL);
	sem[2] = sem_open(__SEM_3, O_RDWR | O_CREAT | O_EXCL, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 0);
	if (sem[2] == SEM_FAILED)
		return (ft_sem_free(sem), ft_pstderr(__ERR_5), NULL);
	return (sem);
}
