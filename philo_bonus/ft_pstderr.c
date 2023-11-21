/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pstderr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:17:15 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/19 12:11:52 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

ssize_t	ft_pstderr(const char *str)
{
	return (write(STDERR_FILENO, str, ft_strlen(str) * sizeof(char)));
}
