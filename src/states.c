/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:08 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/19 17:26:53 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	stop_eating(t_info *p)
{
	if (check_death_while_eating(p) == -1 || get_args()->kill == 1)
	{
		pthread_mutex_unlock(get_lock_write());
		return (-1);
	}
	*p->fork_left = false;
	*p->fork_rigth = false;
	p->st = sleeping;
	p->started_sleeping = get_time();
	pthread_mutex_unlock(p->left_fork_m);
	pthread_mutex_unlock(p->rigth_fork_m);
	printer(p->id, p->st);
	if (check_death_while_sleeping(p) == -1)
	{
		pthread_mutex_unlock(get_lock_write());
		return (-1);
	}
	return (0);
}

int	how_many_times_eat(t_info *p)
{
	if (++p->c_eat == get_args()->how_many_times_to_eat)
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
	if (get_args()->kill == 1)
		return ;
	printf("%ld: %d has taken a fork\n", get_time(), id);
	printf("%ld: %d has taken a fork\n", get_time(), id);
	printer(id, st);
}

int	check_full_and_dead(t_info *p)
{
	if (get_args()->full == 1 || get_args()->kill == 1)
	{
		pthread_mutex_unlock(&(*p->left_fork_m));
		pthread_mutex_unlock(&(*p->rigth_fork_m));
		if (get_args()->kill != 1)
		{
			*p->fork_left = false;
			*p->fork_rigth = false;
		}
		return (-1);
	}
	return (1);
}

int	give_forks(t_info *p)
{
	while (*p->fork_left == true || *p->fork_rigth == true)
		if (check_death(p) == -1 || get_args()->kill == 1)
			return (-1);
	pthread_mutex_lock(get_lock());
	if (*p->fork_left == false && *p->fork_rigth == false)
	{
		*p->fork_left = true;
		*p->fork_rigth = true;
		p->st = eating;
		pthread_mutex_lock(&(*p->left_fork_m));
		pthread_mutex_lock(&(*p->rigth_fork_m));
		p->started_eating = get_time();
		fork_printer(p->id, p->st);
		if (get_args()->how_many_times_to_eat != -1)
			get_args()->full = how_many_times_eat(p);
	}
	pthread_mutex_unlock(get_lock());
	return (check_full_and_dead(p));
}
