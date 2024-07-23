/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 17:54:23 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 21:46:34 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	routine_think(t_philo	*philo)
{
	print_state(philo, "is thinking\n");
}

static int	routine_sleep(t_philo	*philo)
{
	print_state(philo, "is sleeping\n");
	if (wait_if_no_death(philo, philo->time_sleep))
		return (1);
	return (0);
}

static int	routine_eat(t_philo	*philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_state(philo, "has taken a fork\n");
	pthread_mutex_lock(philo->l_fork);
	if (death_check(philo))
		return (pthread_mutex_unlock(philo->r_fork), \
			pthread_mutex_unlock(philo->l_fork), 1);
	print_state_eat(philo);
	pthread_mutex_lock(philo->lmeal_mutex);
	philo->time_lmeal = get_curr_time();
	pthread_mutex_unlock(philo->lmeal_mutex);
	if (wait_if_no_death(philo, philo->time_eat))
		return (pthread_mutex_unlock(philo->r_fork), \
			pthread_mutex_unlock(philo->l_fork), 1);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_lock(philo->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

static void	routine_sync(t_philo *philo)
{
	pthread_mutex_lock(philo->start_mutex);
	pthread_mutex_unlock(philo->start_mutex);
	pthread_mutex_lock(philo->lmeal_mutex);
	philo->time_lmeal = get_curr_time();
	pthread_mutex_unlock(philo->lmeal_mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		think;

	philo = (t_philo *) arg;
	if (philo->nbr_philo == 1)
		return (print_state(philo, "has taken a fork\n"), arg);
	think = (philo->time_die - (philo->time_eat * 2) - philo->time_sleep) / 2;
	routine_sync(philo);
	if (philo->id % 2 == 1)
	{
		if (wait_if_no_death(philo, philo->time_eat / 2))
			return (arg);
	}
	while (!death_check(philo))
	{
		if (routine_eat(philo))
			return (arg);
		if (routine_sleep(philo))
			return (arg);
		routine_think(philo);
		if (think > 0)
			wait_if_no_death(philo, think);
	}
	return (arg);
}
