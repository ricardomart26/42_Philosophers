#include "philo.h"

void	assign_fork(t_philo *p, int fork1, int fork2, int id)
{
	p->forks[fork1] = 1;
	p->forks[fork2] = 1;
	p->philo[id] = 1;
}

void	give_forks(t_philo *p, int id)
{
	int i;
	i = -1;
	if (id == 0)
	{
		// printf("id %d\n", id);
		if (p->forks[0] == 0 && p->forks[p->nmr_p - 1] == 0)
			assign_fork(p, 0, id, id);
	}
	else
	{
		// printf("id %d\n", id);
		if (p->forks[id - 1] == 0 && p->forks[id] == 0)
			assign_fork(p, id - 1, id, id);
	}
}

void	put_to_sleep(t_philo *p, int id)
{
	if (p->philo[id] == 0)
	{
		if (id == 0)
		{
			p->forks[id] = 0;
			p->forks[p->nmr_p - 1] = 0;
		}
		else
		{
			p->forks[id] = 0;
			p->forks[id - 1] = 0;
		}
		p->philo[id] = 3;
	}
}

void	think(t_philo *p, int id)
{
	if (p->philo[id] == 3)
		p->philo[id] = 2;
}

void	print_states(int id, int state, int time)
{
	if (state == 1)
		printf("%d: philo %d is eating\n", time, id);
	else if (state == 2)
		printf("%d: philo %d is thinking\n", time, id);
	else if (state == 3)
		printf("%d: philo %d is sleeping\n", time, id);
}

long	get_time()
{
	long time;
	struct timeval t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec/1000);
	return (time);
}

// int	id =  0;
long	calculate_time(long	time)
{
	long time2;
	long diff;

	time2 = get_time();
	diff = time2 - time;
	return (diff);
}


void	*main_funct(void	*arg)
{
	int done;
	long time;
	long timediff;
	int id;

	id = *(int*)arg;
	time = get_time();
	done = 0;

	while (!p.is_dead)
	{
		printf("id %d\n", id);
		pthread_mutex_lock( &p.lock );

		think(&p, id);
		give_forks(&p, id);
		put_to_sleep(&p, id);

		timediff = calculate_time(time);
		pthread_mutex_unlock(&p.lock);
		sleep(2);
		print_states(id, p.philo[id], timediff);
		return (NULL);
	}
}

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
	p->forks = malloc(p->nmr_p * sizeof(bool));
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
	}	
}

int counter = 0;

int main(int ac, char **av)
{
	int i;
	int done;
	int X;

	x = 0;
	done = 0;
	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_to_die time_to_eat time_to_sleep [optional: nbr_of_times_philo_must_eat");
	if (ac == 6)
		p.how_many_times_to_eat = ft_atoi(av[5]);
	init_philo(&p, av, ac);
	i = -1;
	while (++i < p.nmr_p)
	{
		p.forks[i] = -1;
		printf("i %d\n", i);
		pthread_create(&p.philo[i].t, NULL, main_funct, &p.philo[i].id);
	}
	i = -1;
	while (++i < p.nmr_p)
		pthread_join(p.t[i], NULL);
}