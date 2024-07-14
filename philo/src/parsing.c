/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 21:07:42 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/14 21:08:22 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	parsing_digits(char *str)
{
	int	i;

	i = 0;
	while (str && ft_isdigit((int) str[i]))
		i++;
	if (str[i] || !i)
		return (-1);
	return (0);
}

static int	parsing(char **argv)
{
	if (input_check_digits(argv[1]))
		return (error("Invalid, number_of_philosophers."));
	if (input_check_digits(argv[2]))
		return (error("Invalid, time_to_die."));
	if (input_check_digits(argv[3]))
		return (error("Invalid, time_to_eat."));
	if (input_check_digits(argv[4]))
		return (error("Invalid, time_to_sleep."));
	if (argv[5] && input_check_digits(argv[5]))
		error("Invalid, number_of_meals.");
	return (0);
}
