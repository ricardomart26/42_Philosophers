/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:41:45 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/24 00:00:25 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	g_kill = 0;

void	init_args(int ac, char **av)
{
	g_args.nbr_philo = ft_atoi(av[1]);
	g_args.time_to_die = ft_atoi(av[2]) * 1000;
	g_args.time_to_eat = ft_atoi(av[3]) * 1000;
	g_args.time_to_sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		g_args.how_many_times_to_eat = ft_atoi(av[5]);
	else
		g_args.how_many_times_to_eat = -1;
}

void	init_mutex(void)
{
	g_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	g_lock2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	g_write_kill = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	g_lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void	init_forks(t_philo *p, int i)
{
	if (i == 0)
	{
		p->philo[i].fork_left = &p->forks[p->nmr_p - 1];
		p->philo[i].fork_rigth = &p->forks[0];
	}
	else
	{
		p->philo[i].fork_left = &p->forks[i - 1];
		p->philo[i].fork_rigth = &p->forks[i];
	}
}

void	init_philo(t_philo *p)
{
	int		i;

	p->nmr_p = g_args.nbr_philo;
	p->philo = ft_calloc(p->nmr_p, sizeof(t_info));
	if (p->philo == NULL)
		return ;
	p->forks = ft_calloc(p->nmr_p, sizeof(bool));
	init_mutex();
	i = -1;
	while (++i < p->nmr_p)
	{
		p->philo[i].id = i + 1;
		p->philo[i].c_eat = 0;
		p->philo[i].started_eating = 0;
		p->philo[i].st = scratch_balls;
		init_forks(p, i);
	}
}
