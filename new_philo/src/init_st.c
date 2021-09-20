#include "philo.h"

void	ft_mutex_init(pthread_mutex_t *mutex);

void	give_forks_to_each_philo(t_philo *philo, int i, t_m *m)
{
	if (i == 0)
	{
		PRINT(m->forks[args.nbr - 1], d)
		PRINT(m->forks[i], d)
		printf("\n");
		philo->fork_right = &m->forks[args.nbr - 1];
		philo->fork_left = &m->forks[i];
		PRINT(*philo->fork_right, d)
		PRINT(*philo->fork_left, d)
		printf("\n");
	}
	else
	{
		PRINT(m->forks[i - 1], d)
		PRINT(m->forks[i], d)
		printf("\n");

		philo->fork_right = &m->forks[i - 1];
		philo->fork_left = &m->forks[i];
		PRINT(*philo->fork_right, d)
		PRINT(*philo->fork_left, d)
		printf("\n");
	}
}

void	received_argv(t_m *m)
{
	int	i;

	i = -1;
	m->philo = malloc(sizeof(t_philo) * args.nbr);
	ft_mutex_init(&mutex.lock);
	ft_mutex_init(&mutex.lock2);
	ft_mutex_init(&mutex.print);
	while (++i < args.nbr)
	{
		m->philo[i].id = i + 1;
		m->philo[i].st = scratch_balls;
		give_forks_to_each_philo(&m->philo[i], i, m);
	}
}

void	ft_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		error_msg("Failed initializing variable\n");
}

void	init_master(t_m *master)
{
	int	i;

	master->forks = malloc(sizeof(bool) * args.nbr );
	i = -1;
	while (++i < args.nbr)
		master->forks[i] = false;
	received_argv(master);
}

void	init_argv(char **av, int ac)
{
	args.ac = ac;
	args.nbr = ft_atoi(av[1]);
	args.time_to_die = ft_atoi(av[2]);
	args.time_to_eat = ft_atoi(av[3]);
	args.time_to_sleep = ft_atoi(av[4]);
	if (args.ac == 6)
		args.nbr_times_to_eat = ft_atoi(av[5]);
}