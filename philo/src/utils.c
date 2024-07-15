/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 14:43:55 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/15 19:11:24 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	death_check(t_philo *philo)
{
	if (pthread_mutex_lock(philo->death_mutex) != 0)
		error("Mutex error.\n");
	if (*(philo->death) == true)
	{
		if (pthread_mutex_unlock(philo->death_mutex) != 0)
			error("Mutex error.\n");
		return (1);
	}
	if (pthread_mutex_unlock(philo->death_mutex) != 0)
		error("Mutex error.\n");
	return (0);
}

size_t	get_curr_time(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) != 0)
		return (error("get_curr_time: gettimeofday error\n"));
	return (timeofday.tv_sec * 1000 + timeofday.tv_usec / 1000);
}

void	print_state(t_philo *philo, char *msg)
{
	size_t	curr_time;

	if (pthread_mutex_lock(philo->write_mutex) != 0)
		error("Mutex error.\n");
	curr_time = (get_curr_time() - philo->time_start);
	printf("%zu %d %s", curr_time, philo->id, msg);
	if (pthread_mutex_unlock(philo->write_mutex) != 0)
		error("Mutex error.\n");
}