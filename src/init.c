#include "philo.h"


void	init_philo(t_philo *p, char **av, int ac)
{
	int i;
	long time;
	int last;

	p->nmr_p = ft_atoi(av[1]);
	last = p->nmr_p - 1;
	if (p->nmr_p < 2)
		exit(0);
	p->philo = ft_calloc(p->nmr_p, sizeof(t_info));
	p->forks = malloc(p->nmr_p * sizeof(bool) + 1);
	p->philo->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	p->philo->lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	p->philo->lock2 = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	i = -1;
	time = get_time();
	while (++i < p->nmr_p)
	{
		p->philo[i].nbr_philo = p->nmr_p;
		if (ac == 6)
			p->philo[i].how_many_times_to_eat = ft_atoi(av[5]);
		p->philo[i].how_many_times_to_eat = 0;
		p->philo[i].id = i;
		p->philo[i].lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		p->philo[i].lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		p->philo[i].time_to_die = ft_atoi(av[2]);
		p->philo[i].time_to_eat = ft_atoi(av[3]);
		p->philo[i].time_to_sleep = ft_atoi(av[4]);
		p->philo[i].last_eat = time;
		p->philo[i].total_eat = 0;
		p->philo[i].st = scratch_balls;
		if (i == 0)
		{
			p->philo[i].fork_left = &p->forks[i];
			p->philo[i].fork_right = &p->forks[last];
		}
		else
		{
			p->philo[i].fork_right = &p->forks[i - 1];
			p->philo[i].fork_left = &p->forks[i];
		}
	}
}
