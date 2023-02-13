/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:35:19 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/25 21:05:57 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	time = ft_time() - philo->t0;
	sem_wait(philo->status);
	printf("%ld ms : %d %s\n", time, philo->id, status);
	sem_post(philo->status);
}

void	sleeping(t_phi *philo)
{
	status(philo, ": is sleeping");
	ft_sleep(philo->life->time_to_sleep);
}

void	thinking(t_phi	*philo)
{
	status(philo, ": is thinking");
}
