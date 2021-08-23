#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# define THREAD_LIMIT 100

typedef struct s_philo
{
	int	nmr_p;
	pthread_t *t;
	int	*philo;
	bool *forks;
	int time_to_eat;
	int time_to_sleep;
	int time_to_die;
	int	how_many_times_to_eat;
	pthread_mutex_t lock;
} t_philo;

#endif