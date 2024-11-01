/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:24:42 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/10/23 17:29:53 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/philo.h"

void	print_status(t_philo *philo, char *status, char *color)
{
	safe_mutex(&philo->data->print, LOCK);
	if (check_death(philo))
	{
		safe_mutex(&philo->data->print, UNLOCK);
		return ;
	}
	if (philo->data->the_end_of_the_world == 0)
		printf(FLUO"%.7ld"END"%s %d %s\n"END, \
		timestamp(philo), color, philo->id, status);
	safe_mutex(&philo->data->print, UNLOCK);
}

void	safe_pthread(t_philo *philo, t_action action)
{
	int	error;

	error = 0;
	if (action == CREATE)
		error = pthread_create(&philo->thread, NULL, routine, philo);
	else if (action == JOIN)
		error = pthread_join(philo->thread, NULL);
	if (error != 0)
		ft_error(ERR_PTHREAD);
}

void	safe_mutex(pthread_mutex_t *mutex, t_action action)
{
	int	error;

	error = 0;
	if (action == INIT)
		error = pthread_mutex_init(mutex, NULL);
	else if (action == DESTROY)
		error = pthread_mutex_destroy(mutex);
	else if (action == LOCK)
		error = pthread_mutex_lock(mutex);
	else if (action == UNLOCK)
		error = pthread_mutex_unlock(mutex);
	if (error != 0)
		ft_error(ERR_MUTEX);
}

int	check_death(t_philo *philo)
{
	safe_mutex(&philo->data->end, LOCK);
	if (philo->data->the_end_of_the_world)
	{
		safe_mutex(&philo->data->end, UNLOCK);
		return (1);
	}
	safe_mutex(&philo->data->end, UNLOCK);
	return (0);
}

int	check_full(t_philo *philo)
{
	if (philo->data->loop != -1 && (philo->meals_eaten == philo->data->loop))
	{
		philo->full = 1;
		return (1);
	}
	return (0);
}
