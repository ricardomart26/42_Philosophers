/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/03 19:12:22 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*g_message[MSG_MAX] = {
	"is eating\n",
	"is sleeping\n",
	"is thinking\n",
	"is dead\n"
};

int		g_kill;

void	printer(int id, t_state state)
{
	if (g_kill == 1)
		return ;
	pthread_mutex_lock(&g_lock_write);
	if (g_kill == 0)
		printf("%ld: %d %s", get_time(), id, g_message[state - 1]);
	pthread_mutex_unlock(&g_lock_write);
}

void	*unlock_eve(t_info *p)
{
	pthread_mutex_unlock(&g_lock);
	pthread_mutex_unlock(&g_lock_write);
	pthread_mutex_unlock(&(*p->left_fork_m));
	pthread_mutex_unlock(&(*p->rigth_fork_m));
	return (NULL);
}

void	*routine(void	*arg)
{
	t_info	philo;
	long	time_passed;

	philo = *(t_info *)arg;
	time_passed = 0;
	while (philo.st != is_dead)
	{
		if (g_kill == 1)
			return (unlock_eve(&philo));
		while (philo.st != eating)
			if (give_forks(&philo, time_passed) == -1)
				return (unlock_eve(&philo));
		time_passed = stop_eating(&philo);
		philo.st = thinking;
		printer(philo.id, philo.st);
	}
	return (NULL);
}

int	finish_philo(t_philo *p)
{
	int	i;

	free(p->forks);
	free(p->philo);
	i = -1;
	while (++i < p->nbr_p)
		pthread_mutex_destroy(&p->forks_m[i]);
	pthread_mutex_destroy(&g_lock);
	pthread_mutex_destroy(&g_lock_write);
	free(p->forks_m);
	return (0);
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	p;

	g_kill = 0;
	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_die time_eat \
			time_sleep [optional: nbr_of_times_philo_must_eat");
	init_args(ac, av);
	if (p.nbr_p == 1)
	{
		printf("%d: %d is dead", g_args.time_to_die / 1000, 1);
		return (0);
	}
	init_philo(&p);
	if (p.nbr_p < 1 || p.nbr_p >= THREAD_LIMIT)
		return (finish_philo(&p));
	i = -1;
	while (++i < p.nbr_p)
		pthread_create(&p.philo[i].t, NULL, routine, &p.philo[i]);
	i = -1;
	while (++i < p.nbr_p)
		pthread_join(p.philo[i].t, NULL);
	return (finish_philo(&p));
}
