/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 18:39:46 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 22:10:22 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	destroy_mutexes(char *err, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].death_mutex);
	}
	pthread_mutex_destroy(&data->write_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	if (err)
		return (error(err));
	return (0);
}

int	error(char *err)
{
	write (2, err, ft_strlen(err));
	return (1);
}
