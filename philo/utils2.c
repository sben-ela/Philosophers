/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:30:31 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/29 22:52:07 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *error)
{
	printf("\033[4;31m ERROR : %s \n", error);
}

void	detache(t_philo *philo)
{
	int	j;

	j = 0;
	while (j < philo->life.number_of_philosophers)
		pthread_detach(philo->philosopher[j++].t_id);
}

int	died(t_philo *philo, int i, int j, long var)
{
	while (i < philo->life.number_of_philosophers)
	{
		pthread_mutex_lock(philo->philosopher[i].lock_nb);
		philo->counter = philo->philosopher[i].nb;
		pthread_mutex_unlock(philo->philosopher[i].lock_nb);
		pthread_mutex_lock(&philo->l_incr);
		if (philo->counter >= philo->life.meals)
			j++;
		pthread_mutex_unlock(&philo->l_incr);
		if (j >= philo->life.number_of_philosophers)
			return (detache(philo), 0);
		pthread_mutex_lock(philo->philosopher[i].lock);
		var = philo->philosopher[i].last_meal;
		pthread_mutex_unlock(philo->philosopher[i].lock);
		if (ft_time() - var > philo->life.time_to_die)
		{
			pthread_mutex_lock(&philo->lockout);
			detache(philo);
			status(&philo->philosopher[i], ": is died");
			return (0);
		}
		i++;
	}
	return (1);
}

void	handle_died(t_philo *philo, int i, int j, long var)
{
	while (1)
	{
		if (!died(philo, i, j, var))
			break ;
		i = 0;
		j = 0;
	}
}

void	thinking(t_phi *philo)
{
	status(philo, ": is thinking");
}
