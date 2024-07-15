/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 17:20:27 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/15 19:11:03 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	monitor_check_starve(t_data	*data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_lock(philos[i].meal_mutex) != 0)
			error("Mutex error.\n");
		if ((philos[i].time_lmeal + philos[i].time_die) >= get_curr_time())
		{
			if (pthread_mutex_unlock(philos[i].meal_mutex) != 0)
				error("Mutex error.\n");
			print_state(&philos[i], "died\n");
			return (1);
		}
		if (pthread_mutex_unlock(philos[i].meal_mutex) != 0)
			error("Mutex error.\n");
		i++;
	}
	return (0);
}

static bool	monitor_check_finish(t_philo *philos)
{
	int		i;
	bool	finished;

	i = 0;
	finished = 1;
	while (finished && i < philos[0].nbr_philo)
	{
		if (pthread_mutex_lock(philos[i].meal_mutex) != 0)
			error("Mutex error.\n");
		if (philos[i].meals_eaten < philos[i].nbr_meals)
			finished = !finished;
		if (pthread_mutex_unlock(philos[i].meal_mutex) != 0)
			error("Mutex error.\n");
		i++;
	}
	return (finished);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	while (1)
	{
		if (data->nbr_meals != -1 && monitor_check_finish(data->philos))
			return (arg);
		if (monitor_check_starve(data, data->philos))
		{
			if (pthread_mutex_lock(&data->death_mutex) != 0)
				error("Mutex error.\n");
			data->death = true;
			if (pthread_mutex_unlock(&data->death_mutex) != 0)
				error("Mutex error.\n");
			return (arg);
		}
	}
	return (arg);
}
