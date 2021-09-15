/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/15 22:11:51 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	g_kill;

long	get_start_time()
{
	struct	timeval beg;
	
	gettimeofday(&beg, NULL);
	
}

void	print_states(int id, t_state st)
{
	if (st == eating)
		printf("%ld: %d is eating\n", get_time(), id);
	else if (st == sleeping)
		printf("%ld: %d is sleeping\n", get_time(), id);
	else if (st == thinking)
		printf("%ld: %d is thinking\n", get_time(), id);
	else if (st == scratch_balls)
		printf("%ld: %d is scratching balls\n", get_time(), id);
}

void	write_states(t_info p)
{
	pthread_mutex_lock(&g_lock_write);
	print_states(p.id, p.st);
	pthread_mutex_unlock(&g_lock_write);
}

void	first_values(t_info *philo)
{
	long	start_time;

	start_time = get_start_time();
	while (philo->st != is_dead)
	{
		while (philo->st != eating)
		{
			give_forks(philo);
			if (philo->st != eating)
				printf("philo %d still waiting\n", philo->id);	
		}
		if (g_kill == 1)
			return ;
		if (philo->st == eating)
			stop_eating(philo);
		if (philo->st == sleeping)
			think(philo);
	}
}

void	*main_funct(void	*arg)
{
	t_info		philo;

	philo = *(t_info *)arg;
	first_values(&philo);
	if (g_kill == 1)
		return (NULL);
	return (NULL);
}

void	free_all(t_info **p, bool **forks)
{
	free(forks);
	free(*p);
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	p;

	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_die time_eat \
			time_sleep [optional: nbr_of_times_philo_must_eat");
	init_philo(&p, av, ac);
	if (p.nmr_p < 2)
		exit(0);
	i = -1;
	while (++i < p.nmr_p)
		pthread_create(&p.philo[i].t, NULL, main_funct, &p.philo[i]);
	i = -1;
	while (++i < p.nmr_p)
		pthread_join(p.philo[i].t, NULL);
	
	free_all(&p.philo, &p.forks);
	return (0);
}
