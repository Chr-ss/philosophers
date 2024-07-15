/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 21:07:42 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/15 19:00:13 by crasche       ########   odam.nl         */
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

int	parsing(char **argv)
{
	if (parsing_digits(argv[1]))
		return (error("Invalid, number_of_philosophers.\n"));
	if (parsing_digits(argv[2]))
		return (error("Invalid, time_to_die.\n"));
	if (parsing_digits(argv[3]))
		return (error("Invalid, time_to_eat.\n"));
	if (parsing_digits(argv[4]))
		return (error("Invalid, time_to_sleep.\n"));
	if (argv[5] && parsing_digits(argv[5]))
		error("Invalid, number_of_meals.\n");
	return (0);
}
