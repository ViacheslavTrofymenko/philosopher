/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:46:22 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/13 15:38:08 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *status);
static void	eat(t_philo *philo);
static void	ft_usleep(size_t ms);

size_t	get_timestamp()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!(*philo->dead))
	{
		eat(philo);
		if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
			break ;
		print_status(philo, C_BLU "is sleeping" C_RESET);
		ft_usleep(philo->time_to_sleep);
		print_status(philo, C_YELLOW "is thinking" C_RESET);
	}
	return (NULL);
}

static void	print_status(t_philo *philo, char *status)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->write_lock);
	if (!(*philo->dead))
	{
		timestamp = get_timestamp() - philo->start_time;
		printf("%zu %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(philo->write_lock);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status(philo, C_MAG "has taken a fork" C_RESET);
	pthread_mutex_lock(philo->r_fork);
	print_status(philo, C_MAG "has taken a fork" C_RESET);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_status(philo, C_GRN "is eating" C_RESET);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < ms)
		usleep(500);
}

