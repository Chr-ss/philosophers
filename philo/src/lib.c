/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lib.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: crasche <crasche@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/06 13:40:19 by crasche       #+#    #+#                 */
/*   Updated: 2024/07/17 21:02:47 by crasche       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <limits.h>

int	ft_isdigit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	const char	*start;

	start = s;
	while (*s++)
		;
	return (s - start);
}

size_t	ft_atoi(const char *nptr)
{
	size_t	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr) == 1)
	{
		if (nbr > (UINT_MAX - (*nptr - 48)) / 10)
			return (0);
		nbr = (nbr * 10) + (*nptr++ - 48);
	}
	return (sign * nbr);
}
