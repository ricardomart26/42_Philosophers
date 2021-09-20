#include "philo.h"

void	fork_is_taken(t_philo *p)
{
	while (*p->fork_left != false && *p->fork_right == false)
	{
		pthread_mutex_unlock(&mutex.lock);
		pthread_mutex_lock(&mutex.lock2);
		pthread_mutex_lock(&mutex.lock);
	}
}

void	start_eating(t_philo *p)
{
	pthread_mutex_lock(&mutex.lock);
	printf("%d fork left st %d, fork right st %d\n", p->id, *p->fork_left, *p->fork_right);
	// PRINT(*p->fork_right, d)
	// PRINT(*p-fork_left, d)
	// PRINT(*p-fork_left, d)
	fork_is_taken(p);
	if (*p->fork_left == false && *p->fork_right == false)
	{
		*p->fork_left = true;
		printf("%d took left fork\n", p->id);
		*p->fork_right = true;
		printf("%d took right fork\n", p->id);
		p->st = eating;
		printf("%d is eating\n", p->id);
		usleep(args.time_to_eat);
	}
	pthread_mutex_unlock(&mutex.lock);
}

void	release_forks(t_philo *p)
{
	p->fork_left = false;
	p->fork_right = false;
	pthread_mutex_unlock(&mutex.lock2);
	p->st = sleeping;
	printf("%d is sleeping\n", p->id);
	usleep(args.time_to_sleep);
}

void	think_einstein(t_philo *p)
{
	p->st = think;
	printf("%d is thinking\n", p->id);
}

void	*start_program(void *arg)
{
	t_philo p;

	p = *(t_philo *)arg;
	while (p.st != died)
	{
		if (p.st != eating)
			start_eating(&p);
		if (p.st == eating)
			release_forks(&p);
		if (p.st == sleeping)
			think_einstein(&p);
		sleep(1);
	}
	printf("Nao devias fazer isto\n");
	return (NULL);
}


int main(int ac, char **av)
{
	t_m		master;
	int		i;

	init_argv(av, ac);
	init_master(&master);
	i = -1;
	while (++i < args.nbr)
		pthread_create(&master.philo[i].t, NULL, start_program, &master.philo[i]);
	i = -1;
	while (++i < args.nbr)
		pthread_join(master.philo[i].t, NULL);
	return (0);
} 
