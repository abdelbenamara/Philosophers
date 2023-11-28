/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/28 08:18:59 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define _DEFAULT_SOURCE

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define __USAGE	"\
Usage: philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n"
# define __ERR_1	"Error: argument value is not a natural number\n"
# define __ERR_2	"Error: argument value is too big\n"
# define __ERR_3	"Error: too many philosophers\n"
# define __ERR_4	"Error: out of memory\n"
# define __ERR_5	"Error: insufficient resources to create another semaphore\n"
# define __ERR_6	"Error: insufficient resources to create another process\n"
# define __ERR_7	"Error: insufficient resources to create another thread\n"

# define __SEM_1	".a556e5d6-4f4c-4f8f-9890-56d8fac98a95"
# define __SEM_2	".b465deb1-73cb-43b5-bbe9-3ecfbbb0a868"
# define __SEM_3	".cd0fb47a-ec57-4204-8a39-a5f527506a2a"
# define __SEM_4	".d9978d1b-72be-4abe-8076-3973286245ae"

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
	size_t			number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			*number_of_times_must_eat;
	size_t			meal_count;
	t_state			state;
	sem_t			*run;
	sem_t			*abort;
	sem_t			*forks;
	sem_t			*meal_goals;
	struct timeval	start;
	struct timeval	global_start;
}	t_philo;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_atos(const char *nptr);
char	*ft_stoa(size_t n);

ssize_t	ft_pstderr(const char *str);

void	ft_sem_free(sem_t **sem);
sem_t	**ft_sem_init(void);

void	ft_routine(t_philo *philo, size_t number, sem_t **sem);
uint8_t	ft_simulate(t_args args);

#endif
