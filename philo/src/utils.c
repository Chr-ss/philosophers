/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 14:43:55 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 21:42:33 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	if (philo->death > 0)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return (0);
}

size_t	get_curr_time(void)
{
	struct timeval	timeofday;

	if (gettimeofday(&timeofday, NULL) != 0)
		return (error("get_curr_time: gettimeofday error\n"));
	return (timeofday.tv_sec * 1000 + timeofday.tv_usec / 1000);
}

void	print_state_eat(t_philo *philo)
{
	size_t	curr_time;

	pthread_mutex_lock(philo->write_mutex);
	curr_time = (get_curr_time() - *(philo->time_start));
	if (death_check(philo))
	{
		pthread_mutex_unlock(philo->write_mutex);
		return ;
	}
	printf("%zu %d has taken a fork\n%zu %d is eating\n", curr_time, \
		philo->id, curr_time, philo->id);
	pthread_mutex_unlock(philo->write_mutex);
}

void	print_state(t_philo *philo, char *msg)
{
	size_t	curr_time;

	pthread_mutex_lock(philo->write_mutex);
	curr_time = (get_curr_time() - *(philo->time_start));
	if (death_check(philo))
	{
		pthread_mutex_unlock(philo->write_mutex);
		return ;
	}
	printf("%zu %d %s", curr_time, philo->id, msg);
	pthread_mutex_unlock(philo->write_mutex);
}

int	wait_if_no_death(t_philo *philo, size_t wait)
{
	size_t	alarm;

	alarm = get_curr_time() + wait;
	while (alarm > get_curr_time())
	{
		if (death_check(philo))
			return (1);
		usleep(200);
	}
	return (0);
}
