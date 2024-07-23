/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 17:20:27 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 21:43:38 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	monitor_print_state(t_philo *philo, char *msg)
{
	size_t	curr_time;

	pthread_mutex_lock(philo->write_mutex);
	curr_time = (get_curr_time() - *(philo->time_start));
	printf("%zu %d %s", curr_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_mutex);
}

static void	monitor_set_death(t_data	*data)
{
	t_philo	*philos;
	int		i;

	philos = data->philos;
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(&philos[i].death_mutex);
		philos[i].death = 1;
		pthread_mutex_unlock(&philos[i].death_mutex);
		i++;
	}
}

static bool	monitor_check_starve(t_data	*data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_lock(philos[i].lmeal_mutex);
		if (get_curr_time() - philos[i].time_lmeal > philos[i].time_die)
		{
			pthread_mutex_unlock(philos[i].lmeal_mutex);
			monitor_set_death(data);
			monitor_print_state(&philos[i], "died\n");
			return (true);
		}
		pthread_mutex_unlock(philos[i].lmeal_mutex);
		i++;
	}
	return (0);
}

static bool	monitor_check_finish(t_data	*data, t_philo *philos)
{
	int		i;
	bool	finished;

	i = 0;
	finished = 1;
	if (philos[0].nbr_meals == -1)
		return (0);
	while (finished && i < philos[0].nbr_philo)
	{
		pthread_mutex_lock(philos[i].meal_mutex);
		if (philos[i].meals_eaten < philos[i].nbr_meals)
			finished = !finished;
		pthread_mutex_unlock(philos[i].meal_mutex);
		i++;
	}
	if (finished)
		monitor_set_death(data);
	return (finished);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *) arg;
	while (1)
	{
		if (monitor_check_finish(data, data->philos) || \
			monitor_check_starve(data, data->philos))
			break ;
	}
	return (arg);
}
