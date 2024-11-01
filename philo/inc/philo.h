/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 11:25:43 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/06/26 13:13:17 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

//colors
# define RED "\033[0;31m"
# define MAUVE "\033[0;34m"
# define DUCK "\033[38;2;8;195;187m"
# define ORANGE "\033[38;2;253;189;68m"
# define PINK "\033[38;2;255;105;180m"
# define FLUO "\033[38;2;223;255;0m"
# define END "\033[0m"

//statut
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define FORK "has taken a fork"
# define DIE "died"

//errors
# define ERR_NB_ARG "Wrong number of arguments, please enter 4 or 5 args.\n"
# define ERR_NB_PHILO "Wrong number of philosophers, at least one please.\n"
# define ERR_NOT_NUMBER "use of invalid characters, please use numbers.\n"
# define ERR_NEGATIVE "please use numbers above zero.\n"
# define ERR_OVERFLOW "use of too large numbers, please use smaller numbers.\n"
# define ERR_GET_TIME "gettimeofday failed.\n"
# define ERR_MALLOC "malloc failed.\n"
# define ERR_PTHREAD "error using pthread.\n"
# define ERR_MUTEX "error using mutexes.\n"

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef enum e_action
{
	CREATE,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
}	t_action;

typedef struct s_data
{
	int				nb_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				loop;
	unsigned long	start;
	int				the_end_of_the_world;
	pthread_mutex_t	end;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int				id;
	unsigned long	last_meal;
	int				meals_eaten;
	int				full;
	pthread_t		thread;
	pthread_mutex_t	fork_lock;
	int				fork;
	t_data			*data;
	t_philo			*next;
}	t_philo;

//philo
void			*routine(void *args);

//utils
int				ft_error(const char *str);
void			print_status(t_philo *philo, char *status, char *color);
void			safe_pthread(t_philo *philo, t_action action);
void			safe_mutex(pthread_mutex_t *mutex, t_action action);
int				check_death(t_philo *philo);
int				check_full(t_philo *philo);

//time_utils
unsigned long	current_time(void);
unsigned long	timestamp(t_philo *philo);
int				check_time_to_die(t_philo *philo);
int				nomnom_usleep(unsigned long time_in_ms, t_philo *philo);
int				deadly_usleep(unsigned long time_in_ms, t_philo *philo);

//libft_utils
size_t			ft_strlen(const char *str);
long int		ft_atol(const char *nptr);
int				ft_atoi(const char *nptr);
int				is_number(const char *str);

#endif
