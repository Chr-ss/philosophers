/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/14 14:43:30 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/14 22:00:46 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
// # include <limits.h>
# include <stdbool.h>
# include <unistd.h>
// # include <stdarg.h>
// # include <limits.h>
// # include <unistd.h>

# define MAX_PHILO 200

typedef struct	s_philo
{
	int				id;
	int				meals;
	int				nbr_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			nbr_meals;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write;
	pthread_mutex_t	*death;
	pthread_mutex_t	*meal;
}	t_philo;

typedef struct	s_data
{
	bool			death;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				nbr_philo;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			nbr_meals;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_mutex_t	meal;
}	t_data;


int		error(char *err);

int		init_data(t_data *data, char **argv, t_philo *philos, pthread_mutex_t *forks);

int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isdigit(int c);
void	ft_bzero(void *s, size_t n);

#endif /* PHILO_H */
