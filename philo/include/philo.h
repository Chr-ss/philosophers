/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 14:43:30 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/16 18:26:46 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <unistd.h>

# define MAX_PHILO 200
# define ARGS_USAGE "ARGS shold be used as follows: \
number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	bool			*death;
	int				meals_eaten;
	int				nbr_philo;
	int				nbr_meals;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			time_start;
	size_t			time_lmeal;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
}	t_philo;

typedef struct s_data
{
	bool			death;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nbr_philo;
	int				nbr_meals;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			time_start;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
}	t_data;

/**
 * @brief Write err to STDERR and return 1
 * @param char *err
 * @return 1
*/
int		error(char *err);

/**
 * @brief Initilaize data struct with arguments
 * @param t_data *data
 * @param char **argv
 * @param t_philo *philos
 * @param pthread_mutex_t *forks
 * @return 0 is succesful operation
 * @exception 1 is unsuccesful operation
*/
int		init_data(t_data *data, char **argv, t_philo *philos, \
				pthread_mutex_t *forks);

/**
 * @brief Calls gettimeofday() to get current time in ms
 * @param void
 * @return current time in ms
 * @exception 1 is unsuccesful operation
*/
size_t	get_curr_time(void);

/**
 * @brief Initial function for monitor thread
 * @param void *arg = t_data *data
 * @return void *arg = t_data *data
*/
void	*monitor(void *arg);

/**
 * @brief Prints message () for philo
 * @param t_philo *philo
 * @param char *msg
 * @return void
*/
void	print_state(t_philo *philo, char *msg);

/**
 * @brief Destroys all mutexes and write err to SDTERR if set
 * @param char *err
 * @param t_data *data
 * @return 1 if err is set
 * @return 0 if err is NULL
*/
int		destroy_mutexes(char *err, t_data *data);

/**
 * @brief Initial function for philo routines
 * @param void *arg = t_data *philo
 * @return void *arg = t_data *philo
*/
void	*routine(void *arg);

/**
 * @brief Parses for invalid input
 * @param char **argv
 * @return 0 if ok, 1 if error
*/
int		parsing(char **argv);

/**
 * @brief Initilizes all philos and forks
 * @param t_data *data
 * @param t_philo *philos
 * @param pthread_mutex_t *forks
 * @return 0 if ok, 1 if error
*/
int		init_philos(t_data *data, t_philo *philos, pthread_mutex_t *forks);

/**
 * @brief Creates threads and joins them when finished
 * @param t_data *data
 * @return 0 if ok, 1 if error
*/
int		thread(t_data *data);

/**
 * @brief Checks for dead philo
 * @param t_philo *philo
 * @return 1 if dead, 0 if not
*/
int		death_check(t_philo *philo);

/**
 * @brief Waits for wait ms while checking for death
 * @param t_philo *philo
 * @param size_t wait
 * @return void
*/
void	wait_if_no_death(t_philo *philo, size_t wait);

size_t	ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);

#endif /* PHILO_H */
