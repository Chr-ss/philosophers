/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 21:14:52 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/14 23:09:20 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	monitor_fuc(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *) arg;
}

int thread(t_data *data)
{
	pthread_t	monito_thread;

	pthread_create(&monito_thread, NULL, &monitor_fuc, data->philos);
	return (0);
}
