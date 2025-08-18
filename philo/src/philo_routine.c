/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:46:22 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/18 11:15:23 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *status);
static void	eat(t_philo *philo);
static void	routine_of_one_philo(t_philo *philo);

size_t	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat / 2 * 1000);
	if (philo->num_of_philos == 1)
	{
		routine_of_one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*(philo->dead))
		{
			pthread_mutex_unlock(philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(philo->dead_lock);
		eat(philo);
		print_status(philo, C_BLU "is sleeping" C_RESET);
		usleep(philo->time_to_sleep * 1000 + 300);
		print_status(philo, C_YELLOW "is thinking" C_RESET);
	}
	return (NULL);
}

static void	print_status(t_philo *philo, char *status)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return ;
	}
	pthread_mutex_unlock(philo->dead_lock);
	timestamp = get_timestamp() - philo->start_time;
	pthread_mutex_lock(philo->print_lock);
	printf("%zu %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(philo->print_lock);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->l_fork < philo->r_fork)
	{
		first_fork = philo->l_fork;
		second_fork = philo->r_fork;
	}
	else
	{
		first_fork = philo->r_fork;
		second_fork = philo->l_fork;
	}
	pthread_mutex_lock(first_fork);
	print_status(philo, C_MAG "has taken a fork" C_RESET);
	pthread_mutex_lock(second_fork);
	print_status(philo, C_MAG "has taken a fork" C_RESET);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_status(philo, C_GRN "is eating" C_RESET);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

static void	routine_of_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, "has taken a fork");
	usleep(philo->time_to_die * 1000);
	pthread_mutex_unlock(philo->l_fork);
}
