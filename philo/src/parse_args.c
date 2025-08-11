/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 13:00:04 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/11 16:09:32 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

static long	ft_atol(char *str)
{
	long	nb;
	int		i;

	nb = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	check_input(char *arg)
{
	int		i;

	i = 0;
	if (arg[0] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	if (i == 0 || (i == 1 && arg[0] == '+'))
		return (1);
	return (0);
}

int	parse_args(int argc, char *argv[], t_program *program)
{
	int	i;

	if (argc != 5 && argc != 6)
		return (printf("Error: wrong number of arguments\n"));
	i = 1;
	while (argv[++i])
	{
		if (check_input(argv[i]) == 1)
			return (printf("Error: invalid argument values\n"), 1);
	}
	program->num_of_philos = (size_t)ft_atol(argv[1]);
	program->time_to_die = (size_t)ft_atol(argv[2]);
	program->time_to_eat = (size_t)ft_atol(argv[3]);
	program->time_to_sleep = (size_t)ft_atol(argv[4]);
	program->num_times_to_eat = -1;
	if (argc == 6)
		program->num_times_to_eat = (int)ft_atol(argv[5]);
	if (program->num_of_philos == 0)
		return (printf("Error: number of philosophers must be greater than 1\n"), 1);
	if (program->time_to_die == 0 || program->time_to_eat == 0 || program->time_to_sleep == 0)
		return (printf("Error: time arguments must be greater than zero\n"), 1);
	if (program->num_times_to_eat < -1)
		return (printf("Error: number of times to eat must be >= 0 or omitted\n"), 1);
	program->dead_flag = false;
	return (0);
}

