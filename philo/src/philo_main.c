/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:25 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/09 13:04:16 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int main(void)
{
	t_philo philo;
	struct	timeval	tv;
	long	seconds;
	long	microseconds;
	long	milliseconds;

	seconds = tv.tv_sec;
	microseconds = tv.tv_usec;
	milliseconds = (seconds / 1000 + microseconds * 1000);

	gettimeofday(&tv, NULL);

	printf("\tid=%d last_meal_time=%ld eat_count=%d \n", philo.id, philo.last_meal_time, philo.eat_count);
	memset(&philo, 0, sizeof(philo));
	printf("\tid=%d last_meal_time=%ld eat_count=%d \n", philo.id, philo.last_meal_time, philo.eat_count);
	return (0);
}
