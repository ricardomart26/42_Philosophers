#include "philo.h"
#include <semaphore.h>

void	print_states(int id, t_state st, int time)
{
	if (st == eating)
		printf("%d: philo %d is eating\n", time, id);
	else if (st == sleeping)
		printf("%d: philo %d is thinking\n", time, id);
	else if (st == thinking)
		printf("%d: philo %d is sleeping\n", time, id);
	else if (st == scratch_balls)
		printf("%d: philo %d is scratching balls\n", time, id);
}


void	*main_funct(void	*arg)
{
	long time;
	long timediff;
	int id;

	id = *(int*)arg;
	time = get_time();


	printf("id %d\n", id);
	pthread_mutex_lock( &p.lock );
	give_forks(&p, id, 0);
	if (p.philo[id].st == scratch_balls)
		put_to_sleep(&p, id);
	think(&p, id);

	timediff = calculate_time(time);
	pthread_mutex_unlock(&p.lock);
	print_states(id, p.philo[id].st, timediff);
	sleep(3);
	while (!p.is_dead)
	{
		// printf("id %d\n", id);
		pthread_mutex_lock( &p.lock );
		if (p.philo[id].st == eating)
			stop_eating(&p, id, timediff);
		if (p.philo[id].st == thinking)
			give_forks(&p, id, timediff);
		// if (p.philo[id].st != sleeping)
		// 	put_to_sleep(&p, id);
		if (p.philo[id].st != thinking)
			think(&p, id);
		timediff = calculate_time(time);
		pthread_mutex_unlock(&p.lock);
		sleep(2);
		print_states(id, p.philo[id].st, timediff);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	int i;

	if (ac < 5)
		printf("\tERRO\n\n\tUsage: ./philo nbr_of_philo time_to_die time_to_eat time_to_sleep [optional: nbr_of_times_philo_must_eat");
	if (ac == 6)
		p.how_many_times_to_eat = ft_atoi(av[5]);
	init_philo(&p, av, ac);
	i = -1;
	while (++i < p.nmr_p)
	{
		p.forks[i] = 0;
		pthread_create(&p.philo[i].t, NULL, main_funct, &p.philo[i].id);
	}
	i = -1;
	while (++i < p.nmr_p)
		pthread_join(p.philo[i].t, NULL);
}
