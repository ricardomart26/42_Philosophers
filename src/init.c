/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:41:45 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/11 23:07:46 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_info **philo, int i)
{
	philo[i]->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo[i]->lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo[i]->lock2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	philo[i]->kill = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void	init_forks(int i, t_info **philo, int last, t_philo *p)
{
	if (i == 0)
	{
		philo[i]->fork_left = &p->forks[i];
		philo[i]->fork_right = &p->forks[last];
	}
	else
	{
		philo[i]->fork_right = &p->forks[i - 1];
		philo[i]->fork_left = &p->forks[i];
	}
}

void	init_philo(t_philo *p, char **av, int ac)
{
	int		i;

	p->nmr_p = ft_atoi(av[1]);
	p->philo = ft_calloc(p->nmr_p, sizeof(t_info));
	if (p->philo == NULL)
		return ;
	p->forks = malloc(p->nmr_p * sizeof(bool) + 1);
	if (p->forks == NULL)
		return ;
	i = -1;
	while (++i < p->nmr_p)
	{
		if (ac == 6)
			p->philo[i].how_many_times_to_eat = ft_atoi(av[5]);
		else
			p->philo[i].how_many_times_to_eat = 0;
		mutex_init(&p->philo, i);
		p->philo[i].id = i;
		p->philo[i].time_to_die = ft_atoi(av[2]);
		p->philo[i].time_to_eat = ft_atoi(av[3]);
		p->philo[i].time_to_sleep = ft_atoi(av[4]);
		p->philo[i].last_eat = 0;
		p->philo[i].total_eat = 0;
		p->philo[i].st = scratch_balls;
		p->forks[i] = false;
		init_forks(i, &p->philo, p->nmr_p - 1, p);
	}
}
