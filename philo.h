#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# define THREAD_LIMIT 100


typedef struct s_info
{
	int id;
	pthread_t t;
	int last_eat;
	int total_eat;
	pthread_mutex_t lock;
	pthread_mutex_t lock_write;
} t_info;

t_philo	p;


typedef struct s_philo
{
	t_info *philo;
	int time_to_sleep;
	int time_to_die;
	int	how_many_times_to_eat;
	int time_to_eat;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	lock;
	bool is_dead;
	int	nmr_p;
	bool *forks;
	struct timeval time;

} t_philo;


int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);


#endif