#include "new_philo.h"

void	received_argv(t_m *master, t_argv args)
{
	int	i;

	i = 0;
	while (i < args.nbr)
	{
		master->philo[i].id = i + 1;
		master->philo[i].st = scratch_balls;
		master->philo[i].fork_left = false;
		master->philo[i].fork_right = false;
		master->philo[i].info.time_to_die = args.time_to_die;
		master->philo[i].info.time_to_eat = args.time_to_eat;
		master->philo[i].info.time_to_sleep = args.time_to_sleep;
		if (args.ac == 6)
			master->philo[i].info.how_many_times_to_eat = args.nbr_times_to_eat;
		i++;
	}
}

void	init_master(t_m *master, t_argv	args)
{
	received_argv(master, args);
	master->forks = malloc(sizeof(bool) * args.nbr);
}

void	init_argv(t_argv *args, char **av, int ac)
{
	args->ac = ac;
	args->nbr = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	if (args->ac == 6)
		args->nbr_times_to_eat = ft_atoi(av[5]);
}

int main(int ac, char **av)
{
	t_m		master;
	t_argv	args;

	init_argv(&args, av, ac);
	init_master(&master, args);
	return (0);
} 
