/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 15:20:06 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/05 20:23:33 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*r1 = (unsigned char *) s1;
	const unsigned char	*r2 = (unsigned char *) s2;

	if (!n)
		return (0);
	while (--n && *r1 && *r2)
	{
		if (*r1 != *r2)
			break ;
		++r1;
		++r2;
	}
	return (*r1 - *r2);
}
