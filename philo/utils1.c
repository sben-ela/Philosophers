/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:40:02 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/29 17:57:50 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	long			time;
	struct timeval	t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (time);
}

void	ft_sleep(long t)
{
	long	time;

	time = ft_time();
	while (ft_time() - time < t)
		usleep(25);
}

void	status(t_phi *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->lockout);
	time = ft_time() - philo->t0;
	printf("%ld ms : %d %s\n", time, philo->id, status);
	pthread_mutex_unlock(&philo->lockout);
}

void	sleeping(t_phi *philo)
{
	status(philo, ": is sleeping");
	ft_sleep(philo->life->time_to_sleep);
}

void	eating(t_phi *philo)
{
	pthread_mutex_lock(philo->fork_r);
	status(philo, ": has taken a fork");
	pthread_mutex_lock(philo->fork_l);
	status(philo, ": has taken a fork");
	status(philo, ": is eating");
	pthread_mutex_lock(philo->lock);
	philo->last_meal = ft_time();
	pthread_mutex_unlock(philo->lock);
	ft_sleep(philo->life->time_to_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}
