/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:46:22 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/17 16:03:38 by vtrofyme         ###   ########.fr       */
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
		ft_usleep(philo->time_to_eat / 2);
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		print_status(philo, "has taken a fork");
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(&philo->l_fork->mutex);
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
		ft_usleep(philo->time_to_sleep);
		print_status(philo, C_YELLOW "is thinking" C_RESET);
	}
	return (NULL);
}

static void	print_status(t_philo *philo, char *status)
{
	size_t timestamp;

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
	if (!philo->l_fork->in_use)
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		philo->l_fork->in_use = true;
		print_status(philo, C_MAG "has taken a fork" C_RESET);
	}
	if (!philo->r_fork->in_use)
	{
		pthread_mutex_lock(&philo->r_fork->mutex);
		philo->r_fork->in_use = true;
		print_status(philo, C_MAG "has taken a fork" C_RESET);
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_status(philo, C_GRN "is eating" C_RESET);
	ft_usleep(philo->time_to_eat);
	philo->l_fork->in_use = false;
	pthread_mutex_unlock(&philo->r_fork->mutex);
	philo->r_fork->in_use = false;
	pthread_mutex_unlock(&philo->l_fork->mutex);
}

static void	ft_usleep(size_t ms)
{
	size_t	start;

	start = get_timestamp();
	while ((get_timestamp() - start) < ms)
		usleep(500);
}

