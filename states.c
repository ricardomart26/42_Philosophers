#include "philo.h"

static	void	remove_fork(t_info *p, long time)
{
	*p->fork_left = false;
	*p->fork_right = false;
	p->st = sleeping;
	printf("%ld: %d is sleeping\n", time, p->id);
	usleep(p->time_to_eat);
}

void	stop_eating(t_info *p, long time)
{
	(void)time;

	if (*p->fork_left == true && *p->fork_right == true)
	{
		printf("%ld: %d has released a fork\n", time, p->id);
		printf("%ld: %d has released a fork\n", time, p->id);
		remove_fork(p, time);
		usleep(p->time_to_sleep);
	}
}


static	void	assign_fork(t_info *p)
{
	*p->fork_left = true;
	*p->fork_right = true;
	p->st = eating;
	usleep(p->time_to_eat);
}

void	give_forks(t_info *p, long time)
{
	(void)time;
	pthread_mutex_lock(&p->lock);
	if (*p->fork_left == false && *p->fork_right == false)
	{
		assign_fork(p);
		printf("%ld: %d has taken a fork\n", time, p->id);
		printf("%ld: %d has taken a fork\n", time, p->id);
		pthread_mutex_unlock(&p->lock);
		usleep(p->time_to_eat);
	}
}

// void	put_to_sleep(t_info *p)
// {
// 	if (p->st == eating || p->st == scratch_balls)
// 	{
// 		if (p->id == 0)
// 		{
// 			p->forks[p->id] = 0;
// 			p->forks[p->nmr_p - 1] = 0;
// 		}
// 		else
// 		{
// 			p->forks[p->id] = 0;
// 			p->forks[p->id - 1] = 0;
// 		}
// 		p->st = sleeping;
// 		usleep(p->time_to_sleep);
// 	}
// }

void	think(t_info *p, long time)
{
	(void)time;
	p->st = thinking;
	// sleep(p->time_to_sleep);
}
