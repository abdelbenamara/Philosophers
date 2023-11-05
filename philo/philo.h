/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/05 22:27:30 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define DEBUG 	"DEBUG - "
# define USAGE	"\
Usage: philo\
 number_of_philosophers\
 time_to_die\
 time_to_eat\
 time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n"
# define ERR_1	"Error: argument is not a natural number\n"
# define ERR_2	"Error: argument is a number too big\n"

typedef struct s_args
{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	*number_of_times_each_philosopher_must_eat;
}	t_args;

/* ************************************************************************** */
/*                                                                            */
/*                                   utils                                    */
/*                                                                            */
/* ************************************************************************** */

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_atos(const char *nptr);
char	*ft_stoa(size_t n);

ssize_t	ft_pstderr(const char *str);

/* ************************************************************************** */
/*                                                                            */
/*                                 arguments                                  */
/*                                                                            */
/* ************************************************************************** */

void	ft_clear_args(t_args *args);
t_args	*ft_init_args(char **strs);

#endif
