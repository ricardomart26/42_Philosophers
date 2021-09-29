/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 05:58:14 by rimartin          #+#    #+#             */
/*   Updated: 2021/09/29 22:32:25 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*main_funct(void	*arg)
{
	t_info	philo;
	long	time_passed;

	philo = *(t_info *)arg;
	while (philo.st != is_dead)
	{
		while (philo.st != eating)
			give_forks(&philo, time_passed);
		if (philo.st == eating)
			time_passed = stop_eating(&philo);
		philo.st = thinking;
		pthread_mutex_lock(&g_lock_write);
		printf("%ld: %d is thinking\n", get_time(), philo.id);
		pthread_mutex_unlock(&g_lock_write);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int		i;
	t_philo	p;

	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_die time_eat \
			time_sleep [optional: nbr_of_times_philo_must_eat");
	init_args(ac, av);
	init_philo(&p);
	if (p.nmr_p < 1)
		exit(0);
	else if (p.nmr_p == 1)
	{
		printf("%d: %d is dead", g_args.time_to_die / 1000, 1);
		free(p.forks);
		free(p.philo);
		return (0);
	}
	i = -1;
	while (++i < p.nmr_p)
		pthread_create(&p.philo[i].t, NULL, main_funct, &p.philo[i]);
	i = -1;
	while (++i < p.nmr_p)
		pthread_join(p.philo[i].t, NULL);
	free(p.forks);
	free(p.philo);
	return (0);
}
