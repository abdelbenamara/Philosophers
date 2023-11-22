/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/22 13:15:15 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_philo_setup(t_philo *philo, t_args args, sem_t **sem)
{
	size_t	i;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].id = -1;
		philo[i].time_to_die = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_to_sleep = args.time_to_sleep;
		philo[i].number_of_times_must_eat
			= args.number_of_times_each_philosopher_must_eat;
		philo[i].meal_count = 0;
		philo[i].state = thinking;
		philo[i].stop = sem[0];
		philo[i].forks = sem[1];
		philo[i].meal_goal = sem[2];
		sem_post(philo->forks);
		++i;
	}
}

static uint8_t	ft_philo_fork(t_philo *philo, t_args args, sem_t **sem)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < args.number_of_philosophers)
	{
		philo[i].id = fork();
		if (philo[i].id == -1)
		{
			j = 0;
			while (j < i)
			{
				kill(philo[j].id, SIGKILL);
				waitpid(philo[i].id, NULL, WUNTRACED);
				++j;
			}
			return (0);
		}
		if (!philo[i].id)
			return (ft_routine(philo, i, sem), 1);
		++i;
	}
	return (1);
}

static void	ft_philo_wait(t_philo *philo, t_args args)
{
	size_t	i;

	sem_wait(philo->stop);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		kill(philo[i].id, SIGKILL);
		waitpid(philo[i].id, NULL, WUNTRACED);
		++i;
	}
}

uint8_t	ft_simulate(t_args args)
{
	sem_t	**sem;
	t_philo	*philo;

	if (!args.number_of_philosophers)
		return (1);
	sem = ft_sem_init();
	if (!sem)
		return (0);
	philo = malloc(args.number_of_philosophers * sizeof(t_philo));
	if (!philo)
		return (ft_sem_free(sem), ft_pstderr(__ERR_4), 0);
	ft_philo_setup(philo, args, sem);
	if (!ft_philo_fork(philo, args, sem))
		return (ft_sem_free(sem), free(philo), ft_pstderr(__ERR_6), 0);
	ft_philo_wait(philo, args);
	ft_sem_free(sem);
	free(philo);
	return (1);
}
