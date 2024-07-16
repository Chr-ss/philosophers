/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 17:54:23 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/16 18:21:36 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	routine_think(t_philo	*philo)
{
	print_state(philo, "is thinking\n");
}

void	routine_sleep(t_philo	*philo)
{
	print_state(philo, "is sleeping\n");
	wait_if_no_death(philo, philo->time_sleep);
}

void	routine_eat(t_philo	*philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->l_fork);
	print_state(philo, "has taken a fork\n");
	print_state(philo, "is eating\n");
	wait_if_no_death(philo, philo->time_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meals_eaten++;
	philo->time_lmeal = get_curr_time();
	pthread_mutex_unlock(philo->meal_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->id % 2 == 0)
		usleep(2 * 1000);
	if (philo->nbr_philo == 1)
	{
		print_state(philo, "has taken a fork\n");
		usleep(philo->time_die * 1000);
		print_state(philo, "died\n");
		return (arg);
	}
	while (1)
	{
		routine_eat(philo);
		if (death_check(philo))
			return (arg);
		routine_sleep(philo);
		if (death_check(philo))
			return (arg);
		routine_think(philo);
		if (death_check(philo))
			return (arg);
	}
	return (arg);
}
