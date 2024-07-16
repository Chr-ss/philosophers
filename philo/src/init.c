/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 18:55:29 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/16 18:21:08 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	init_data_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_data(t_data *data, char **argv, t_philo *philos, \
				pthread_mutex_t *forks)
{
	data->philos = philos;
	data->forks = forks;
	data->death = false;
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->time_start = get_curr_time();
	if (argv[5])
		data->nbr_meals = (int) ft_atoi(argv[5]);
	else
		data->nbr_meals = -1;
	if (data->nbr_philo < 1 || data->nbr_philo > MAX_PHILO || \
		(data->nbr_meals != -1 && data->nbr_meals <= 0))
		return (error("Invalid input!\n"));
	if (init_data_mutex(data))
		return (1);
	return (0);
}

static int	init_philos_forks(t_data *data, t_philo *philos, \
				pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			return (1);
		if (i == 0)
			philos[i].l_fork = &forks[data->nbr_philo - 1];
		else
			philos[i].l_fork = &forks[i - 1];
	}
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	if (init_philos_forks(data, philos, forks))
		return (1);
	while (++i < data->nbr_philo)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].death = &data->death;
		philos[i].write_mutex = &data->write_mutex;
		philos[i].death_mutex = &data->death_mutex;
		philos[i].meal_mutex = &data->meal_mutex;
		philos[i].r_fork = &forks[i];
		philos[i].nbr_philo = data->nbr_philo;
		philos[i].time_die = data->time_die;
		philos[i].time_eat = data->time_eat;
		philos[i].time_sleep = data->time_sleep;
		philos[i].nbr_meals = data->nbr_meals;
		philos[i].time_start = data->time_start;
		philos[i].time_lmeal = data->time_start;
	}
	return (0);
}
