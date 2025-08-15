/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:27:26 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/15 19:53:07 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mutexes(t_program *pm);

void	free_all(t_program *pm)
{
	destroy_mutexes(pm);
	if (pm->forks)
	{
		free(pm->forks);
		pm->forks = NULL;
	}
	if (pm->philos)
	{
		free(pm->philos);
		pm->philos = NULL;
	}
}

static void	destroy_mutexes(t_program *pm)
{
	size_t	i;

	if (pm->forks && pm->forks_initialized)
	{
		i = 0;
		while (i < pm->num_of_philos)
		{
			pthread_mutex_destroy(&pm->forks[i]);
			i++;
		}
	}
	if (pm->locks_initialized)
	{
		pthread_mutex_destroy(&pm->dead_lock);
		pthread_mutex_destroy(&pm->meal_lock);
		pthread_mutex_destroy(&pm->print_lock);
	}
}
