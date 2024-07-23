/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 18:55:29 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 21:07:05 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(t_data *data, char **argv, t_philo *philos, \
				pthread_mutex_t *forks)
{
	data->philos = philos;
	data->forks = forks;
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
		data->time_die == 0 || data->time_sleep == 0 || \
		data->time_start == 0 || (data->nbr_meals != -1 \
		&& data->nbr_meals <= 0))
		return (error("Invalid input!\n"));
	pthread_mutex_init(&data->write_mutex, NULL);
	pthread_mutex_init(&data->lmeal_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->start_mutex, NULL);
	return (0);
}

static int	init_philos_forks(t_data *data, t_philo *philos, \
				pthread_mutex_t *forks, int i)
{
	pthread_mutex_init(&forks[i], NULL);
	philos[i].r_fork = &forks[i];
	if (i == 0)
		philos[i].l_fork = &forks[data->nbr_philo - 1];
	else
		philos[i].l_fork = &forks[i - 1];
	return (0);
}

int	init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		init_philos_forks(data, philos, forks, i);
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].death = 0;
		pthread_mutex_init(&philos[i].death_mutex, NULL);
		philos[i].write_mutex = &data->write_mutex;
		philos[i].lmeal_mutex = &data->lmeal_mutex;
		philos[i].meal_mutex = &data->meal_mutex;
		philos[i].start_mutex = &data->start_mutex;
		philos[i].nbr_philo = data->nbr_philo;
		philos[i].time_die = data->time_die;
		philos[i].time_eat = data->time_eat;
		philos[i].time_sleep = data->time_sleep;
		philos[i].nbr_meals = data->nbr_meals;
		philos[i].time_start = &data->time_start;
		philos[i].time_lmeal = get_curr_time();
	}
	return (0);
}
