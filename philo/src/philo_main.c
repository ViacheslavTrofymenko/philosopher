/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:25 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/12 00:00:50 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int main(int argc, char *argv[])
{
	t_program	pm;

	if(parse_args(argc, argv, &pm))
		return (free_all(&pm), 1);
	if(init_mutexes(&pm))
		return (free_all(&pm), 1);
	if (init_philos(&pm))
		return(free_all(&pm), 1);
	return (0);
}
