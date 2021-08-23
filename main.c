#include "philo.h"

// int is_first_or_last()
// {
// 	if (i == )
// }


int	*give_forks(t_philo *p)
{
	int *arr;
	int i;
	int nmr;

	nmr = p->forks - 1;
	i = -1;
	arr = malloc(sizeof(int *) * p->nmr_p + 1);
	while (++i < p->nmr_p)
	{
		if (i == 0)
		{
			if (p->forks[i] == 0 && p->forks[nmr] == 0)
			{
				p->forks[0] = 1;
				p->forks[nmr] = 1;
			}
		}
		else if (i == nmr)
		{
			if (p->forks[0] == 0 && p->forks[i] == 0)
			{
				p->forks[0] = 1;
				p->philo[nmr] = 1;
			}
		}
		else
		{
			if (p->forks[i - 1] == 0 && p->forks[i] == 0)
			{
				p->forks[i - 1] = 1;
				p->forks[i] = 1;
			}
		}
	}
}

void	*main_funct(void	*arg)
{
	pthread_mutex_t lock;
	int *arr;

	arr = (int *)arg;
	lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

}

void	init_threads(t_philo p)
{
	int i;
	int done;
	int	*arr;
	int counter;

	counter = 0;
	done = 0;
	while (!done)
	{
		if (counter == 0)
			give_forks(&p);
		i = -1;
		while (++i < p.nmr_p)
			pthread_create(&p.t[i], NULL, main_funct, arr);
		i = -1;
		while (++i < p.nmr_p)
			pthread_join(p.t[i], NULL);
		counter++;
	}
}

void	init_philo(t_philo *p, char **av)
{
	p->nmr_p = ft_atoi(av[1]);
	if (p->nmr_p < 2)
		exit(0);
	p->time_to_die = ft_atoi(av[2]);
	p->time_to_eat = ft_atoi(av[3]);
	p->time_to_sleep = ft_atoi(av[4]);
	p->forks = ft_calloc(p->nmr_p, sizeof(bool));
	p->how_many_times_to_eat = 0;
	p->t = malloc(sizeof(pthread_t) * p->nmr_p + 1);
	p->philo = ft_calloc(p->nmr_p, sizeof(int));
	p->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

int main(int ac, char **av)
{
	t_philo p;

	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_to_die time_to_eat time_to_sleep [optional: nbr_of_times_philo_must_eat");
	init_philo(&p, av);
	if (ac == 6)
		p.how_many_times_to_eat = ft_atoi(av[5]);
	init_threads(p);
}