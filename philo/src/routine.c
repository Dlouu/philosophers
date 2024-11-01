/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:38:38 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/06/26 13:42:36 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	forking(t_philo *philo, pthread_mutex_t *fork_lock, int *fork)
{
	while (1)
	{
		if (check_time_to_die(philo) || check_death(philo) || check_full(philo))
			return (1);
		safe_mutex(fork_lock, LOCK);
		if (*fork)
		{
			*fork = 0;
			print_status(philo, FORK, PINK);
			safe_mutex(fork_lock, UNLOCK);
			return (0);
		}
		safe_mutex(fork_lock, UNLOCK);
	}
}

static int	sleeping_and_thinking(t_philo *philo)
{
	if (check_full(philo))
		return (1);
	print_status(philo, SLEEP, MAUVE);
	if (deadly_usleep(philo->data->time_to_sleep, philo))
		return (1);
	print_status(philo, THINK, DUCK);
	return (0);
}

static int	eating_odd(t_philo *philo)
{
	if (check_full(philo))
		return (1);
	print_status(philo, EAT, ORANGE);
	philo->last_meal = current_time();
	if (nomnom_usleep(philo->data->time_to_eat, philo))
		return (1);
	safe_mutex(&philo->next->fork_lock, LOCK);
	safe_mutex(&philo->fork_lock, LOCK);
	philo->fork = 1;
	philo->next->fork = 1;
	safe_mutex(&philo->fork_lock, UNLOCK);
	safe_mutex(&philo->next->fork_lock, UNLOCK);
	philo->meals_eaten += 1;
	return (0);
}

static int	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		if (check_full(philo))
			return (1);
		print_status(philo, EAT, ORANGE);
		philo->last_meal = current_time();
		if (nomnom_usleep(philo->data->time_to_eat, philo))
			return (1);
		safe_mutex(&philo->fork_lock, LOCK);
		safe_mutex(&philo->next->fork_lock, LOCK);
		philo->fork = 1;
		philo->next->fork = 1;
		safe_mutex(&philo->next->fork_lock, UNLOCK);
		safe_mutex(&philo->fork_lock, UNLOCK);
		philo->meals_eaten += 1;
		return (0);
	}
	else
		return (eating_odd(philo));
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	print_status(philo, THINK, DUCK);
	if (philo->id % 2 == 0)
		nomnom_usleep(5, philo);
	while (1)
	{
		if (forking(philo, &philo->fork_lock, &philo->fork))
			return (NULL);
		if (forking(philo, &philo->next->fork_lock, &philo->next->fork))
			return (NULL);
		if (eating(philo))
			return (NULL);
		if (sleeping_and_thinking(philo))
			return (NULL);
	}
	return (NULL);
}
