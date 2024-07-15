/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 21:14:52 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/15 19:24:21 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int thread(t_data *data)
{
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	philos = data->philos;
	if (pthread_create(&monitor_thread, NULL, &monitor, data) != 0)
		return (destroy_mutexes("thread: pthread_create error", data));
	while (i < data->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (destroy_mutexes("thread: pthread_create error", data));
		i++;
	}
	if (pthread_join(monitor_thread, NULL) != 0)
		return (destroy_mutexes("thread: pthread_join error1", data));
	while (--i >= 0)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (destroy_mutexes("thread: pthread_join error2", data));
	}
	return (0);
}
