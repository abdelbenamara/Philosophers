/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atos.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:21:48 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/19 12:11:54 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_atos(const char *nptr)
{
	size_t	i;

	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	i = 0;
	if (*nptr == '+')
		++nptr;
	while ('0' <= *nptr && *nptr <= '9')
	{
		i = i * 10 + (*nptr - '0');
		++nptr;
	}
	return (i);
}
