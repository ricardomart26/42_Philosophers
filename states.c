#include "philo.h"

static	void	remove_fork(t_philo *p, int fork1, int fork2, int id)
{
	p->forks[fork1] = 0;
	p->forks[fork2] = 0;
	p->philo[id].st = sleeping;
	usleep(p->time_to_eat);
}

void	stop_eating(t_philo *p, int id, long time)
{
	if (id == 0)
	{
		if (p->forks[0] == 1 && p->forks[p->nmr_p - 1] == 1)
		{
			remove_fork(p, 0, id, id);
			printf("%ld: %d has released a fork\n", time, id);
			printf("%ld: %d has released a fork\n", time, id);
			usleep(p->time_to_sleep);
		}
	}
	else
	{
		if (p->forks[id - 1] == 1 && p->forks[id] == 1)
		{
			remove_fork(p, id - 1, id, id);
			printf("%ld: %d has released a fork\n", time, id);
			printf("%ld: %d has released a fork\n", time, id);
			usleep(p->time_to_sleep);
		}
	}
}


static	void	assign_fork(t_philo *p, int fork1, int fork2, int id)
{
	p->forks[fork1] = 1;
	p->forks[fork2] = 1;
	p->philo[id].st = eating;
	usleep(p->time_to_eat);
}

void	give_forks(t_philo *p, int id, long time)
{
	if (id == 0)
	{
		if (p->forks[0] == 0 && p->forks[p->nmr_p - 1] == 0)
		{
			assign_fork(p, 0, id, id);
			printf("%ld: %d has taken a fork\n", time, id);
			printf("%ld: %d has taken a fork\n", time, id);
			usleep(p->time_to_sleep);
		}
	}
	else
	{
		if (p->forks[id - 1] == 0 && p->forks[id] == 0)
		{
			assign_fork(p, id - 1, id, id);
			printf("%ld: %d has taken a fork\n", time, id);
			printf("%ld: %d has taken a fork\n", time, id);
			usleep(p->time_to_sleep);
		}
	}
}

void	put_to_sleep(t_philo *p, int id)
{
	if (p->philo[id].st == eating || p->philo[id].st == scratch_balls)
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
		p->philo[id].st = sleeping;
		usleep(p->time_to_sleep);
	}
}

void	think(t_philo *p, int id)
{
	if (p->philo[id].st == sleeping)
		p->philo[id].st = thinking;
}

