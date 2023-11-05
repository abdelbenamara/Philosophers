/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:24:13 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/05 20:33:45 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	size_t_to_strlen(size_t n)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = n;
	if (!n)
		++len;
	while (i > 0)
	{
		++len;
		i = i / 10;
	}
	return (len);
}

char	*ft_stoa(size_t n)
{
	size_t	i;
	size_t	len;
	char	*a;

	i = n;
	len = size_t_to_strlen(n);
	a = malloc((len + 1) * sizeof(char));
	if (!a)
		return (NULL);
	a[len] = '\0';
	if (!n)
		a[0] = '0';
	while (i > 0)
	{
		--len;
		a[len] = i % 10 + '0';
		i = i / 10;
	}
	return (a);
}
