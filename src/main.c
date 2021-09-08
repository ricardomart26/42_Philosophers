/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/08 11:32:09 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int g_kill = 0;
#define PRINT_VAR(X) printf(#X " is %ld and the address is %p\n", X, &X);

void	print_states(int id, t_state st, long time)
{
	if (st == eating)
		printf("%ld: %d is eating\n", time, id);
	else if (st == sleeping)
		printf("%ld: %d is sleeping\n", time, id);
	else if (st == thinking)
		printf("%ld: %d is thinking\n", time, id);
	else if (st == scratch_balls)
		printf("%ld: %d is scratching balls\n", time, id);
}

void	write_states(t_info p, long timediff)
{
	pthread_mutex_lock(&p.lock_write);
	print_states(p.id, p.st, timediff);
	pthread_mutex_unlock(&p.lock_write);
}

void	first_values(t_info *p, long *timediff, long time)
{
	while (p->st != is_dead)
	{
		while (p->st != eating)
			give_forks(p, 0);
		if (p->st == is_dead)
		{
			pthread_mutex_lock(&p->kill);
			g_kill = 1;
			pthread_mutex_unlock(&p->kill);
		}
		if (g_kill == 1)
			return ;
		if (p->st == eating)
			stop_eating(p, time);
		if (p->st == sleeping)
			think(p, time);
		*timediff = calculate_time(time);
		sleep(3);
	}
}

void	*main_funct(void	*arg)
{
	long time;
	long timediff;
	t_info philo;
	
	philo = *(t_info *)arg;
	time = get_time();
	first_values(&philo, &timediff, time);
	if (g_kill == 1)
		return ;
	sleep(3);
	write_states(philo, timediff);
	while (philo.st != is_dead)
	{
		if (philo.st == eating)
			stop_eating(&philo, timediff);
		else if (philo.st == thinking)
			give_forks(&philo, timediff);
		else if (philo.st == sleeping)
			philo.st = thinking;
		timediff = calculate_time(time);
		print_states(philo.id, philo.st, timediff);
		sleep(2);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	int i;
	t_philo p;

	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_to_die time_to_eat time_to_sleep [optional: nbr_of_times_philo_must_eat");
	init_philo(&p, av, ac);
	i = -1;
	while (++i < p.nmr_p)
	{
		p.forks[i] = 0;
		pthread_create(&p.philo[i].t, NULL, main_funct, &p.philo[i]);
	}
	i = -1;
	while (++i < p.nmr_p)
		pthread_join(p.philo[i].t, NULL);
}
