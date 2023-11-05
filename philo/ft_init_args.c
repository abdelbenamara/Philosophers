/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:19:59 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/05 22:45:43 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static uint8_t	ft_is_natural_number(const char *nptr)
{
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '+')
		++nptr;
	while (*nptr)
	{
		if (*nptr < '0' || '9' < *nptr)
			break ;
		++nptr;
	}
	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr)
		return (0);
	return (1);
}

static uint8_t	ft_setup_arg(size_t *nb, const char *nptr)
{
	size_t	i;
	char	*s;

	while (*nptr == ' ' || (9 <= *nptr && *nptr <= 13))
		++nptr;
	if (*nptr == '+')
		++nptr;
	i = ft_atos(nptr);
	s = ft_stoa(i);
	if (!s)
		return (0);
	if (ft_strncmp(s, nptr, ft_strlen(s)))
		return (ft_pstderr(ERR_2), free(s), 0);
	free(s);
	*nb = i;
	return (1);
}

static t_args	*ft_parse_args(char **strs)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	if (!ft_setup_arg(&(args->number_of_philosophers), strs[0]))
		return (free(args), NULL);
	if (!ft_setup_arg(&(args->time_to_die), strs[1]))
		return (free(args), NULL);
	if (!ft_setup_arg(&(args->time_to_eat), strs[2]))
		return (free(args), NULL);
	if (!ft_setup_arg(&(args->time_to_sleep), strs[3]))
		return (free(args), NULL);
	args->number_of_times_each_philosopher_must_eat = NULL;
	if (!(strs[4]))
		return (args);
	args->number_of_times_each_philosopher_must_eat = malloc(sizeof(size_t));
	if (!(args->number_of_times_each_philosopher_must_eat))
		return (free(args), NULL);
	if (!ft_setup_arg(args->number_of_times_each_philosopher_must_eat, strs[4]))
		return (ft_clear_args(args), NULL);
	return (args);
}

t_args	*ft_init_args(char **strs)
{
	size_t	i;
	t_args	*args;

	i = 0;
	while (strs[i])
	{
		if (!ft_is_natural_number(strs[i]))
			return (ft_pstderr(ERR_1), NULL);
		++i;
	}
	args = ft_parse_args(strs);
	if (!args)
		return (NULL);
	return (args);
}
