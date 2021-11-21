/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/22 19:53:20 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*g_message[MSG_MAX] = {
	"is eating\n",
	"is sleeping\n",
	"is thinking\n",
	"is dead\n"
};

t_info	*unlock_eve(t_info *p)
{
	pthread_mutex_unlock(&g_lock);
	pthread_mutex_unlock(&g_lock_write);
	pthread_mutex_unlock(&(*p->left_fork_m));
	pthread_mutex_unlock(&(*p->rigth_fork_m));
	return (p);
}

void	printer(int id, t_state state)
{
	if (g_args.kill == 1)
		return ;
	pthread_mutex_lock(&g_lock_write);
	if (!g_args.kill)
		printf("%ld: %d %s", get_time(), id, g_message[state - 1]);
	pthread_mutex_unlock(&g_lock_write);
}

void	*routine(void	*arg)
{
	t_info	philo;

	philo = *(t_info *)arg;
	while (g_args.kill != 1)
	{
		while (philo.st != eating)
			if (give_forks(&philo) == -1)
				return (NULL);
		if (stop_eating(&philo) == -1)
			return (NULL);
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
	while (++i < g_args.nbr_philo)
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

	g_args.kill = 0;
	if (ac < 5)
		printf("\tERRO\n\tUsage: ./philo nbr_of_philo time_die time_eat \
time_sleep [optional: nbr_of_times_philo_must_eat");
	init_args(ac, av);
	if (g_args.nbr_philo == 1)
	{
		get_time();
		usleep(g_args.time_to_die * 1000);
		printf("%ld: %d is dead", get_time(), 1);
		return (0);
	}
	init_philo(&p);
	if (g_args.nbr_philo < 1 || g_args.nbr_philo >= THREAD_LIMIT)
		return (finish_philo(&p));
	i = -1;
	while (++i < g_args.nbr_philo)
		pthread_create(&p.philo[i].t, NULL, routine, &p.philo[i]);
	i = -1;
	while (++i < g_args.nbr_philo)
		pthread_join(p.philo[i].t, NULL);
	return (finish_philo(&p));
}
