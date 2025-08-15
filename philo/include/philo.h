/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:22 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/15 19:54:42 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

# define C_RED "\001\x1B[31m\002"
# define C_GRN "\001\x1B[32m\002"
# define C_YELLOW "\001\x1B[33m\002"
# define C_BLU "\001\x1B[34m\002"
# define C_MAG "\001\x1B[35m\002"
# define C_RESET "\001\x1B[0m\002"
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				num_times_to_eat;
	bool			eating;
	bool			*dead;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	size_t			num_of_philos;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*print_lock;
}					t_philo;

typedef struct s_program
{
	size_t			num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
	bool			dead_flag;
	bool			forks_initialized;
	bool			locks_initialized;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}					t_program;

int		parse_args(int argc, char *argv[], t_program *pm);
int		init_mutexes(t_program *pm);
int		init_philos(t_program *pm);
void	free_all(t_program *pm);
void	*philo_routine(void *arg);
void	monitor(t_program *pm);
size_t	get_timestamp();

#endif
