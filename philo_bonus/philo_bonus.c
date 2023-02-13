/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-ela <sben-ela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:36:48 by sben-ela          #+#    #+#             */
/*   Updated: 2023/01/31 22:22:13 by sben-ela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_phi *philosopher)
{
	sem_wait(philosopher->forks);
	status(philosopher, ": has taken a fork");
	sem_wait(philosopher->forks);
	status(philosopher, ": has taken a fork");
	status(philosopher, ": is eating");
	philosopher->last_meal = ft_time();
	ft_sleep(philosopher->life->time_to_eat);
	sem_post(philosopher->forks);
	sem_post(philosopher->forks);
}

void	routine(t_phi *philosopher)
{
	pthread_t	t1;
	static int	flag;

	pthread_create(&t1, NULL, handle_died, philosopher);
	if (philosopher->life->meals == 0)
		flag = 1;
	while (philosopher->nb < philosopher->life->meals || flag)
	{
		eating(philosopher);
		sleeping(philosopher);
		thinking(philosopher);
		philosopher->nb++;
	}
	exit (0);
}

int	full_philo(t_philo *philo, char **av)
{
	if (av[5] && av[5][0] == '0' && av[5][1] == '\0')
		return (0);
	philo->life.number_of_philosophers = ft_atoi(av[1]);
	philo->life.time_to_die = ft_atoi(av[2]);
	philo->life.time_to_eat = ft_atoi(av[3]);
	philo->life.time_to_sleep = ft_atoi(av[4]);
	philo->life.meals = ft_atoi(av[5]);
	philo->philosopher = malloc(sizeof(t_phi)
			* philo->life.number_of_philosophers);
	if (!philo->philosopher)
		ft_error("malloc can't allocate");
	if (philo->life.number_of_philosophers == -1
		|| philo->life.time_to_die == -1 || philo->life.time_to_eat == -1
		|| philo->life.time_to_sleep == -1 || philo->life.meals == -1)
		ft_error("invalid argument");
	return (1);
}

void	creat_philos(t_philo *philo, sem_t *forks, sem_t *status)
{
	int			*p_id;
	int			i;

	i = 0;
	philo->time = ft_time();
	p_id = malloc(sizeof(int) * philo->life.number_of_philosophers);
	if (!p_id)
		ft_error("malloc can't allocate");
	while (i < philo->life.number_of_philosophers)
	{
		p_id[i] = fork();
		if (!p_id[i])
		{
			philo->philosopher[i].nb = 0;
			philo->philosopher[i].t0 = philo->time;
			philo->philosopher[i].last_meal = philo->time ;
			philo->philosopher[i].life = &philo->life;
			philo->philosopher[i].id = i + 1;
			philo->philosopher[i].forks = forks;
			philo->philosopher[i].status = status;
			routine(&philo->philosopher[i]);
		}
		i++;
	}
	kill_processes(philo, p_id);
}

int	main(int ac, char **av)
{
	sem_t	*status;
	sem_t	*forks;
	t_philo	philo;

	sem_unlink("forks");
	sem_unlink("status");
	if (ac != 5 && ac != 6)
		ft_error("invalid number of argument");
	forks = sem_open("forks", O_CREAT | O_EXCL, 0644, ft_atoi(av[1]));
	if (forks == SEM_FAILED)
		ft_error("File exist");
	status = sem_open("status", O_CREAT | O_EXCL, 0644, 1);
	if (status == SEM_FAILED)
		ft_error("File exist");
	if (!full_philo(&philo, av))
		return (0);
	creat_philos(&philo, forks, status);
	sem_close(forks);
	sem_unlink("forks");
	sem_unlink("status");
}
