#include "philo.h"


void	init_philo(t_philo *p, char **av, int ac)
{
	int i;
	long time;

	p->nmr_p = ft_atoi(av[1]);
	if (p->nmr_p < 2)
		exit(0);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	p->forks = malloc(p->nmr_p * sizeof(bool) + 1);
	if (ac == 6)
		p->how_many_times_to_eat = ft_atoi(av[5]);
	p->how_many_times_to_eat = 0;
	p->philo = ft_calloc(p->nmr_p, sizeof(int));
	p->is_dead = false;
	p->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	p->lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	i = -1;
	time = get_time();
	while (++i < p->nmr_p)
	{
		p->philo[i].id = i;
		p->philo[i].lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		p->philo[i].lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
		p->philo[i].last_eat = time;
		p->philo[i].total_eat = 0;
		p->philo[i].st = scratch_balls;
	}
}
