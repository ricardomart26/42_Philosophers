/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/24 00:05:03 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	remove_fork(t_info *p)
{
	*p->fork_left = false;
	*p->fork_rigth = false;
	p->st = sleeping;
}

long	stop_eating(t_info *p)
{
	long	time_passed;	

	time_passed = 0;
	if (*p->fork_left == true && *p->fork_rigth == true)
	{
		time_passed = check_death_while_eating(p);
		remove_fork(p);
		pthread_mutex_lock(&g_lock_write);
		printf("%ld: %d is sleeping\n", get_time(), p->id);
		pthread_mutex_unlock(&g_lock_write);
		time_passed = check_death_while_sleeping(p, time_passed);
	}
	return (time_passed);
}

static	void	assign_fork(t_info *p)
{
	*p->fork_left = true;
	*p->fork_rigth = true;
	p->st = eating;
}

long	check_death(long time_passed, t_info *p)
{
	if (time_passed >= g_args.time_to_die)
	{
		pthread_mutex_lock(&g_lock_write);
		p->st = is_dead;
		printf("%ld: %d is dead\n", get_time() - 10, p->id);
		exit(0);
	}
	usleep(6);
	time_passed += 10;
	return (time_passed);
}

void	how_many_times_eat(t_info *p)
{
	p->c_eat++;
	if (p->c_eat == g_args.how_many_times_to_eat)
	{
		pthread_mutex_lock(&g_lock_write);
		printf("%ld: %d as eaten %d\n", get_time(), p->id, p->c_eat);
		exit(0);
	}
}

void	give_forks(t_info *p, long time_passed)
{
	while (*p->fork_left == true || *p->fork_rigth == true)
		time_passed = check_death(time_passed, p);
	pthread_mutex_lock(&g_lock);
	if (*p->fork_left == false && *p->fork_rigth == false)
	{
		assign_fork(p);
		p->started_eating = get_time();
		printf("%ld: %d has taken a fork\n", get_time(), p->id);
		printf("%ld: %d has taken a fork\n", get_time(), p->id);
		printf("%ld: %d is eating\n", get_time(), p->id);
		if (g_args.how_many_times_to_eat != -1)
			how_many_times_eat(p);
		pthread_mutex_unlock(&g_lock);
	}
	else
		pthread_mutex_unlock(&g_lock);
}
