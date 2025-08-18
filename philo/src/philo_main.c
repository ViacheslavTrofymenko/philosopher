/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:25 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/18 09:47:14 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_program	pm;
	size_t		i;

	memset(&pm, 0, sizeof(pm));
	if (parse_args(argc, argv, &pm))
		return (1);
	if (init_mutexes(&pm))
		return (free_all(&pm), 1);
	if (init_philos(&pm))
		return (free_all(&pm), 1);
	i = 0;
	while (i < pm.num_of_philos)
	{
		pthread_create(&pm.philos[i].thread, NULL,
			philo_routine, &pm.philos[i]);
		i++;
	}
	monitor(&pm);
	i = -1;
	while (++i < pm.num_of_philos)
		pthread_join(pm.philos[i].thread, NULL);
	free_all(&pm);
	return (0);
}
