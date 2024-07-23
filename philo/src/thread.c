/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 21:14:52 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 22:05:29 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	thread(t_data *data)
{
	t_philo		*philos;
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	philos = data->philos;
	pthread_mutex_lock(&data->start_mutex);
	while (i < data->nbr_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
			return (destroy_mutexes("thread: pthread_create error", data));
		i++;
	}
	data->time_start = get_curr_time();
	pthread_mutex_unlock(&data->start_mutex);
	if (pthread_create(&monitor_thread, NULL, &monitor, data) != 0)
		return (destroy_mutexes("thread: pthread_create error", data));
	if (pthread_join(monitor_thread, NULL) != 0)
		return (destroy_mutexes("thread: pthread_join error1", data));
	while (--i >= 0)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (destroy_mutexes("thread: pthread_join error2", data));
	}
	return (0);
}
