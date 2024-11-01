/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:08:20 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/06/26 13:13:56 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	clean_exit(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	if (!*philo)
		return ;
	while (++i < data->nb_philo - 1)
		safe_mutex(&(*philo)[i].fork_lock, DESTROY);
	safe_mutex(&(*data).print, DESTROY);
	safe_mutex(&(*data).end, DESTROY);
	free(*philo);
}

static void	philo_init(t_philo *philo, int i, t_data *data)
{
	(philo)[i].id = i + 1;
	(philo)[i].data = data;
	(philo)[i].meals_eaten = 0;
	(philo)[i].last_meal = data->start;
	(philo)[i].full = 0;
	(philo)[i].fork = 1;
	safe_mutex(&(philo)[i].fork_lock, INIT);
	if (i == data->nb_philo - 1)
		(philo)[i].next = &(philo)[0];
	else
		(philo)[i].next = &(philo)[i + 1];
}

static int	create_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philo)
		return (ft_error(ERR_MALLOC), 1);
	safe_mutex(&data->end, INIT);
	safe_mutex(&data->print, INIT);
	data->start = current_time();
	while (++i < data->nb_philo)
		philo_init(*philo, i, data);
	i = -1;
	while (++i < data->nb_philo)
		safe_pthread(&(*philo)[i], CREATE);
	i = -1;
	while (++i < data->nb_philo)
		safe_pthread(&(*philo)[i], JOIN);
	return (0);
}

static int	error_parsing(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (ft_error(ERR_NB_ARG), 1);
	if (argc == 6)
		data->loop = ft_atoi(argv[5]);
	else
		data->loop = -1;
	if (ft_atoi(argv[1]) < 1)
		return (ft_error(ERR_NB_PHILO), 1);
	while (argc-- > 1)
	{
		if (!is_number(argv[argc]))
			return (ft_error(ERR_NOT_NUMBER), 1);
		if (ft_atoi(argv[argc]) <= 0)
			return (ft_error(ERR_NEGATIVE), 1);
		if (ft_atoi(argv[argc]) != ft_atol(argv[argc]))
			return (ft_error(ERR_OVERFLOW), 1);
	}
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->the_end_of_the_world = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (error_parsing(argc, argv, &data))
		return (EXIT_FAILURE);
	if (create_philo(&philo, &data))
		return (EXIT_FAILURE);
	clean_exit(&philo, &data);
	return (EXIT_SUCCESS);
}
