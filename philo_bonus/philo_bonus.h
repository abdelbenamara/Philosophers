/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/21 02:09:32 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define _DEFAULT_SOURCE

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define __FORKS	".c71774fe-b9a4-4541-8121-87059fa47eda"

# define __USAGE	"\
Usage: philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n"
# define __ERR_1	"Error: argument value is not a natural number\n"
# define __ERR_2	"Error: argument value is too big\n"
# define __ERR_3	"Error: too many philosophers\n"
# define __ERR_4	"Error: out of memory\n"
# define __ERR_5	"Error: insufficient resources to create another semaphore\n"
# define __ERR_6	"Error: insufficient resources to create another process\n"

typedef struct s_args
{
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	*number_of_times_each_philosopher_must_eat;
}	t_args;

typedef enum e_state
{
	thinking,
	eating,
	sleeping
}	t_state;

typedef struct s_philo
{
	pid_t			id;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			*number_of_times_must_eat;
	size_t			meal_count;
	t_state			state;
	struct timeval	start;
}	t_philo;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_atos(const char *nptr);
char	*ft_stoa(size_t n);

ssize_t	ft_pstderr(const char *str);

void	ft_routine(t_philo *philo, size_t number, sem_t *forks);
uint8_t	ft_simulate(t_args args, sem_t *forks);

#endif
