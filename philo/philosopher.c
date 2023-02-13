/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:05:06 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/31 16:37:42 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	second_routine(t_phi *philo, int flag, int i)
{
	while (philo->nb < philo->life->meals || flag)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(philo->lock_nb);
		philo->nb += i;
		pthread_mutex_unlock(philo->lock_nb);
	}
	return ;
}

void	*routine(void *phi)
{
	static int	flag;
	int			i;
	t_phi		*philo;

	i = 1;
	philo = (t_phi *)phi;
	if (philo->id % 2 == 0)
		usleep(50);
	if (philo->life->meals == 0)
	{
		i = 0;
		pthread_mutex_lock(philo->l_increment);
		philo->life->meals++;
		pthread_mutex_unlock(philo->l_increment);
		flag = 1;
	}
	second_routine(philo, flag, i);
	return (0);
}

void	*creat_threads(t_philo *philo, int i)
{
	while (i < philo->life.number_of_philosophers)
	{
		philo->philosopher[i].l_increment = &philo->l_incr;
		philo->philosopher[i].lock_nb = &philo->lnb;
		philo->philosopher[i].lock = &philo->llm;
		philo->philosopher[i].id = i + 1;
		philo->philosopher[i].life = &philo->life;
		philo->philosopher[i].lockout = philo->lockout;
		philo->philosopher[i].nb = 0;
		philo->philosopher[i].t0 = philo->t0;
		philo->philosopher[i].fork_r = &philo->lock[i];
		if (i == philo->life.number_of_philosophers - 1)
			philo->philosopher[i].fork_l = &philo->lock[0];
		else
			philo->philosopher[i].fork_l = &philo->lock[i + 1];
		pthread_mutex_lock(philo->philosopher[i].lock);
		philo->philosopher[i].last_meal = philo->t0;
		pthread_mutex_unlock(philo->philosopher[i].lock);
		pthread_create(&philo->philosopher[i].t_id, NULL,
			&routine, &philo->philosopher[i]);
		usleep(100);
		i++;
	}
	handle_died(philo, 0, 0, 0);
	return (0);
}

int	full_philo(t_philo *philo, char **av)
{
	philo->t0 = ft_time();
	if (av[1][0] == '0' && av[1][1] == '\0')
		return (0);
	if (av[5] && av[5][0] == '0' && av[5][1] == '\0')
		return (0);
	philo->life.number_of_philosophers = ft_atoi(av[1]);
	philo->life.time_to_die = ft_atoi(av[2]);
	philo->life.time_to_eat = ft_atoi(av[3]);
	philo->life.time_to_sleep = ft_atoi(av[4]);
	philo->life.meals = ft_atoi(av[5]);
	if (philo->life.number_of_philosophers == -1
		|| philo->life.time_to_die == -1 || philo->life.time_to_eat == -1
		|| philo->life.time_to_sleep == -1 || philo->life.meals == -1)
	{
		ft_error("invalid argument");
		return (0);
	}
	philo->lock = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	if (!philo->lock)
		return (0);
	philo->philosopher = malloc(sizeof(t_phi)
			* philo->life.number_of_philosophers);
	if (!philo->philosopher)
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	static int			i;
	t_philo				philo;

	if (ac != 5 && ac != 6)
	{
		ft_error("invalid number of argument");
		return (0);
	}
	if (!full_philo(&philo, av))
		return (0);
	if (pthread_mutex_init(&philo.lnb, NULL))
		return (0);
	if (pthread_mutex_init(&philo.l_incr, NULL))
		return (0);
	if (pthread_mutex_init(&philo.llm, NULL))
		return (0);
	if (pthread_mutex_init(&philo.lockout, NULL))
		return (0);
	while (i < philo.life.number_of_philosophers)
	{
		if (pthread_mutex_init(&philo.lock[i], NULL))
			return (0);
		i++;
	}
	creat_threads(&philo, 0);
}
