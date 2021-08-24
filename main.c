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
		p->philo[id] = 3;
}

void	think(t_philo *p, int id)
{
	if (p->philo[id] == 1)
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
	// printf("time %ld\n", time);
	return (time);
}

void	*main_funct(void	*arg)
{
	int done;
	int id;
	long time;
	// printf("nmr_p %d\n", *(int*)arg);
	id =  *(int*)arg;
	
	time = get_time();
	// printf("id %d\n", id);
	// printf("time %ld\n", p.time.tv_sec);
	done = 0;
	pthread_mutex_lock(&p.lock);
	think(&p, id);
	give_forks(&p, id);
	put_to_sleep(&p, id);
	pthread_mutex_unlock(&p.lock);
	print_states(id, p.philo[id], time);
	sleep(2);
	return (NULL);
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
	p->is_dead = false;
	p->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	p->lock_write = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

int counter = 0;

int main(int ac, char **av)
{
	int i;
	int done;

	done = 0;
	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_to_die time_to_eat time_to_sleep [optional: nbr_of_times_philo_must_eat");
	if (ac == 6)
		p.how_many_times_to_eat = ft_atoi(av[5]);
	init_philo(&p, av);
	i = -1;
	while (++i < p.nmr_p)
		pthread_create(&p.t[i], NULL, main_funct, (void*)&i);
	i = -1;
	while (++i < p.nmr_p)
		pthread_join(p.t[i], NULL);
}