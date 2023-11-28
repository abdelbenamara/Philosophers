/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 19:54:11 by abenamar          #+#    #+#             */
/*   Updated: 2023/11/28 08:18:57 by abenamar         ###   ########.fr       */
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
		philo[i].number = i + 1;
		philo[i].time_to_die = args.time_to_die;
		philo[i].time_to_eat = args.time_to_eat;
		philo[i].time_to_sleep = args.time_to_sleep;
		philo[i].number_of_times_must_eat
			= args.number_of_times_each_philosopher_must_eat;
		philo[i].meal_count = 0;
		philo[i].state = thinking;
		philo[i].abort = sem[0];
		philo[i].forks = sem[1];
		philo[i].meal_goals = sem[2];
		philo[i].run = sem[3];
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

static void	*ft_meal_goals_routine(void *arg)
{
	t_philo	*philo;
	size_t	i;

	philo = (t_philo *) arg;
	i = 0;
	while (i < philo->number)
	{
		sem_post(philo->forks);
		++i;
	}
	i = 0;
	while (i < philo->number)
	{
		sem_wait(philo->meal_goals);
		++i;
	}
	sem_post(philo->abort);
	return (NULL);
}

static void	ft_philo_wait(t_philo *philo, t_args args)
{
	size_t		i;
	pthread_t	id;

	if (pthread_create(&id, NULL, &ft_meal_goals_routine, \
		&philo[args.number_of_philosophers - 1]))
	{
		ft_pstderr(__ERR_7);
		sem_post(philo->abort);
	}
	sem_post(philo->run);
	sem_wait(philo->abort);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		sem_post(philo->meal_goals);
		kill(philo[i].id, SIGKILL);
		waitpid(philo[i].id, NULL, WUNTRACED);
		++i;
	}
	pthread_join(id, NULL);
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
