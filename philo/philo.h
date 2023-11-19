/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:12:40 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/19 11:20:40 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define _DEFAULT_SOURCE

# include <pthread.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define __USAGE	"\
Usage: philo number_of_philosophers time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n"
# define __ERR_1	"Error: argument value is not a natural number\n"
# define __ERR_2	"Error: argument value is too big\n"
# define __ERR_3	"Error: too many philosophers\n"
# define __ERR_4	"Error: out of memory\n"
# define __ERR_5	"Error: insufficient resources to create another mutex\n"
# define __ERR_6	"Error: insufficient resources to create another thread\n"

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

typedef struct s_lock
{
	uint8_t			acquired;
	pthread_mutex_t	mutex;
}	t_lock;

typedef struct s_philo
{
	pthread_t		id;
	size_t			number;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			*number_of_times_must_eat;
	size_t			meal_count;
	t_state			state;
	t_lock			*run;
	t_lock			*abort;
	t_lock			*left_fork;
	t_lock			*right_fork;
	t_lock			*meal_goal;	
	struct timeval	start;
}	t_philo;

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

size_t	ft_atos(const char *nptr);
char	*ft_stoa(size_t n);

ssize_t	ft_pstderr(const char *str);

void	ft_lock_free(t_lock *lock, size_t size);
t_lock	*ft_lock_init(size_t size);
uint8_t	ft_lock_acquire(t_lock *lock);
void	ft_lock_release(t_lock *lock);
uint8_t	ft_lock_locked(t_lock *lock);

void	*ft_routine(void *arg);
uint8_t	ft_simulate(t_args args);

#endif
