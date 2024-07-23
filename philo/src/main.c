/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 14:39:29 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 15:31:38 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	fork[MAX_PHILO];

	if (argc < 5 || argc > 6)
		return (error(ARGS_USAGE));
	if (parsing(argc, argv))
		return (1);
	if (init_data(&data, argv, philos, fork))
		return (1);
	if (init_philos(&data, philos, fork))
		return (1);
	if (thread(&data))
		return (1);
	return (destroy_mutexes(NULL, &data));
}
