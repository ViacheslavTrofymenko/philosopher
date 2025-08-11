/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 10:10:25 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/11 16:19:00 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int main(int argc, char *argv[])
{
	t_program	program;

	if(parse_args(argc, argv, &program))
		return (1);
	if(init_mutexes(&program))
		return (1);
	init_philos(&program);

	return (0);
}
