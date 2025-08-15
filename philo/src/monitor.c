/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 13:51:49 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/15 20:24:56 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static bool	all_have_eaten(t_program *pm);

void	monitor(t_program *pm)
{
	size_t	i;

	while (1)
	{
		i = -1;
		while (++i < pm->num_of_philos)
		{
			pthread_mutex_lock(&pm->meal_lock);
			if ((get_timestamp() - pm->philos[i].last_meal) > pm->time_to_die)
			{
				pthread_mutex_unlock(&pm->meal_lock);
				pthread_mutex_lock(&pm->dead_lock);
				pm->dead_flag = true;
				pthread_mutex_unlock(&pm->dead_lock);
				pthread_mutex_lock(&pm->print_lock);
				printf(C_RED "%zu %d died\n" C_RESET, get_timestamp() - pm->philos[i].start_time,
					pm->philos[i].id);
				pthread_mutex_unlock(&pm->print_lock);
				return ;
			}
			pthread_mutex_unlock(&pm->meal_lock);
		}
		if (all_have_eaten(pm))
		{
			pthread_mutex_lock(&pm->dead_lock);
			pm->dead_flag = true;
			pthread_mutex_unlock(&pm->dead_lock);
			return ;
		}
		usleep(1000);
	}
}

static bool	all_have_eaten(t_program *pm)
{
	size_t	i;
	int		full_count;

	full_count = 0;
	i = 0;
	while (i < pm->num_of_philos)
	{
		pthread_mutex_lock(&pm->meal_lock);
		if (pm->philos[i].num_times_to_eat != -1 &&
			pm->philos[i].meals_eaten >= pm->philos[i].num_times_to_eat)
			full_count++;
		pthread_mutex_unlock(&pm->meal_lock);
		i++;
	}
	return (full_count == (int)pm->num_of_philos);
}
