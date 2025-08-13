/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:05:26 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/13 16:23:28 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static void init_philo(t_program *pm, size_t i);

int	init_mutexes(t_program *pm)
{
	size_t	i;

	pm->forks = malloc(sizeof(pthread_mutex_t) * pm->num_of_philos);
	if (!pm->forks)
		return (printf(C_RED "Error: malloc forks failed.\n" C_RESET), 1);
	i = 0;
	while(++i < pm->num_of_philos)
	{
		if (pthread_mutex_init(&pm->forks[i], NULL) != 0)
			return (printf(C_RED "Error: fork init failed.\n" C_RESET), 1);
	}
	if (pthread_mutex_init(&pm->dead_lock, NULL) != 0)
		return (printf(C_RED "Error: dead_lock init failed.\n" C_RESET), 1);
	if (pthread_mutex_init(&pm->meal_lock, NULL) != 0)
		return (printf(C_RED "Error: meal_lock init failed.\n" C_RESET), 1);
	if (pthread_mutex_init(&pm->write_lock, NULL) != 0)
		return (printf(C_RED "Error: write_lock init failed.\n" C_RESET), 1);
	return (0);
}
int	init_philos(t_program *pm)
{
	size_t	i;

	pm->philos = malloc(sizeof(t_philo) * pm->num_of_philos);
	if (!pm->philos)
		return (printf(C_RED "Error: malloc philo failed.\n" C_RESET), 1);
	i = 0;
	while (i < pm->num_of_philos)
	{
		init_philo(pm, i);
		i++;
	}
	return (0);
}

static void init_philo(t_program *pm, size_t i)
{
	t_philo	*philo;

	philo = &pm->philos[i];
	philo->id = (int)(i + 1);
	philo->meals_eaten = 0;
	philo->num_times_to_eat = pm->num_times_to_eat;
	philo->eating = false;
	philo->dead = &pm->dead_flag;
	philo->last_meal = get_timestamp();
	philo->time_to_die = pm->time_to_die;
	philo->time_to_eat = pm->time_to_eat;
	philo->time_to_sleep = pm->time_to_sleep;
	philo->start_time = get_timestamp();
	philo->write_lock = &pm->write_lock;
	philo->dead_lock = &pm->dead_lock;
	philo->meal_lock = &pm->meal_lock;
	philo->l_fork = &pm->forks[i];
	philo->r_fork = &pm->forks[(i + 1) % pm->num_of_philos];
}
