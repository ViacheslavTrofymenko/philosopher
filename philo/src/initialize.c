/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:19:16 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/11 16:28:13 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_program *program)
{
	int i;

	if (pthread_mutex_init(&program->dead_lock, NULL))
		return (printf("Error: failed to init dead_lock\n"), 1);
	if (pthread_mutex_init(&program->meal_lock, NULL))
		return (printf("Error: failed to init meal_lock\n"), 1);
	if (pthread_mutex_init(&program->write_lock, NULL))
		return (printf("Error: failed to init write_lock\n"), 1);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
	if (!program->forks)
		return (printf("Error: malloc forks failed\n"), 1);

	i = 0;
	while (i < (int)program->num_of_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL))
			return (printf("Error: failed to init fork mutex\n"), 1);
		i++;
	}
	return (0);
}
int init_philos(t_program *program)
{
	size_t i;

	program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	if (!program->philos)
		return (printf("Error: malloc philos failed\n"), 1);
	i = 0;
	while (++i < program->num_of_philos)
	{
		program->philos[i].id = (int)(i + 1);
		program->philos[i].num_of_philos = program->num_of_philos;
		program->philos[i].num_times_to_eat = program->num_times_to_eat;
		program->philos[i].time_to_die = program->time_to_die;
		program->philos[i].time_to_eat = program->time_to_eat;
		program->philos[i].time_to_sleep = program->time_to_sleep;
		program->philos[i].dead = &program->dead_flag;
		program->philos[i].eating = false;
		program->philos[i].meals_eaten = 0;
		program->philos[i].last_meal = 0;
		program->philos[i].start_time = ft_get_current_time();
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].l_fork = &program->forks[i];
		program->philos[i].r_fork = &program->forks[(i + 1) % program->num_of_philos];
	}
	return (0);
}
