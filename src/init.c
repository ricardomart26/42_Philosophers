/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 02:41:45 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/19 17:22:17 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(int ac, char **av)
{
	get_args()->nbr_philo = ft_atoi(av[1]);
	get_args()->full = 0;
	get_args()->kill = 0;
	get_args()->time_to_die = ft_atoi(av[2]);
	get_args()->time_to_eat = ft_atoi(av[3]);
	get_args()->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		get_args()->how_many_times_to_eat = ft_atoi(av[5]);
	else
		get_args()->how_many_times_to_eat = -1;
}

void	init_mutex(t_philo *p)
{
	int	i;

	i = -1;
	*get_lock() = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	*get_lock_write() = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	while (++i < get_args()->nbr_philo)
		p->forks_m[i] = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

void	init_forks(t_philo *p, int i)
{
	if (i == 0)
	{
		p->philo[i].left_fork_m = &p->forks_m[0];
		p->philo[i].rigth_fork_m = &p->forks_m[get_args()->nbr_philo - 1];
		p->philo[i].fork_left = &p->forks[0];
		p->philo[i].fork_rigth = &p->forks[get_args()->nbr_philo - 1];
	}
	else
	{
		p->philo[i].left_fork_m = &p->forks_m[i];
		p->philo[i].rigth_fork_m = &p->forks_m[i - 1];
		p->philo[i].fork_left = &p->forks[i];
		p->philo[i].fork_rigth = &p->forks[i - 1];
	}
}

void	init_philo(t_philo *p)
{
	int		i;

	p->philo = ft_calloc(get_args()->nbr_philo, sizeof(t_info));
	if (p->philo == NULL)
		return ;
	p->forks = ft_calloc(get_args()->nbr_philo, sizeof(bool));
	p->forks_m = ft_calloc(get_args()->nbr_philo, sizeof(pthread_mutex_t));
	init_mutex(p);
	i = -1;
	while (++i < get_args()->nbr_philo)
	{
		p->philo[i].id = i + 1;
		p->philo[i].c_eat = 0;
		p->philo[i].started_eating = 0;
		p->philo[i].started_sleeping = 0;
		p->philo[i].st = scratch_balls;
		init_forks(p, i);
	}
}
