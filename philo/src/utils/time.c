/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:13:39 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/23 17:30:55 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

unsigned long	timestamp(t_philo *philo)
{
	unsigned long	start;
	struct timeval	time;

	start = philo->data->start;
	if (gettimeofday(&time, NULL) == -1)
		ft_error(ERR_GET_TIME);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start);
}

unsigned long	current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error(ERR_GET_TIME);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_time_to_die(t_philo *philo)
{
	if ((current_time() - philo->last_meal) >= philo->data->time_to_die)
	{
		if (philo->data->the_end_of_the_world == 0)
			print_status(philo, DIE, RED);
		safe_mutex(&philo->data->end, LOCK);
		philo->data->the_end_of_the_world = 1;
		safe_mutex(&philo->data->end, UNLOCK);
		return (1);
	}
	return (0);
}

int	nomnom_usleep(unsigned long time_in_ms, t_philo *philo)
{
	long int	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
	{
		if (check_death(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

int	deadly_usleep(unsigned long time_in_ms, t_philo *philo)
{
	long int	start_time;

	start_time = current_time();
	while ((current_time() - start_time) < time_in_ms)
	{
		if (check_death(philo))
			return (1);
		if ((check_time_to_die(philo)))
			return (1);
		usleep(100);
	}
	return (0);
}
