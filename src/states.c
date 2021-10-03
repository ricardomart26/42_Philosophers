/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/03 21:09:02 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	stop_eating(t_info *p)
{
	long	time_passed;	

	time_passed = check_death_while_eating(p);
	if (g_args.kill == 1)
	{
		pthread_mutex_unlock(&g_lock_write);
		return (-1);
	}
	*p->fork_left = false;
	*p->fork_rigth = false;
	p->st = sleeping;
	pthread_mutex_unlock(p->left_fork_m);
	pthread_mutex_unlock(p->rigth_fork_m);
	printer(p->id, p->st);
	time_passed = check_death_while_sleeping(p, time_passed);
	return (time_passed);
}

long	check_death(long time_passed, t_info *p)
{
	if (time_passed >= g_args.time_to_die)
	{
		p->st = is_dead;
		printer(p->id, p->st);
		if (g_args.kill == 1)
			return (-1);
		g_args.kill = 1;
		return (-1);
	}
	usleep(6);
	time_passed += 10;
	return (time_passed);
}

int	how_many_times_eat(t_info *p)
{
	if (++p->c_eat == g_args.how_many_times_to_eat)
	{
		printf("%ld: %d is full %d\n", get_time(), p->id, p->c_eat);
		pthread_mutex_unlock(p->left_fork_m);
		pthread_mutex_unlock(p->rigth_fork_m);
		return (1);
	}
	return (0);
}

void	fork_printer(int id, t_state st)
{
	if (g_args.kill == 1)
		return ;
	printf("%ld: %d has taken a fork\n", get_time(), id);
	printf("%ld: %d has taken a fork\n", get_time(), id);
	printer(id, st);
}

int	check_full_and_dead(t_info *p)
{
	if (g_args.full == 1 || g_args.kill == 1)
	{
		pthread_mutex_unlock(&(*p->left_fork_m));
		pthread_mutex_unlock(&(*p->rigth_fork_m));
		if (g_args.kill != 1)
		{
			*p->fork_left = false;
			*p->fork_rigth = false;
		}
		return (-1);
	}
	return (1);
}

int	give_forks(t_info *p, long time_passed)
{
	while (*p->fork_left == true || *p->fork_rigth == true)
	{
		time_passed = check_death(time_passed, p);
		if (time_passed == -1 || g_args.kill == 1)
			return (-1);
	}
	pthread_mutex_lock(&g_lock);
	if (*p->fork_left == false && *p->fork_rigth == false)
	{
		*p->fork_left = true;
		*p->fork_rigth = true;
		p->st = eating;
		pthread_mutex_lock(&(*p->left_fork_m));
		pthread_mutex_lock(&(*p->rigth_fork_m));
		p->started_eating = get_time();
		fork_printer(p->id, p->st);
		if (g_args.how_many_times_to_eat != -1)
			g_args.full = how_many_times_eat(p);
	}
	pthread_mutex_unlock(&g_lock);
	return (check_full_and_dead(p));
}
