#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>
# define THREAD_LIMIT 100


typedef enum s_state
{
	scratch_balls,
	eating,
	sleeping,
	thinking
} t_state;

typedef struct s_info
{
	int id;
	pthread_t t;
	int last_eat;
	int total_eat;
	t_state st;
	pthread_mutex_t lock;
	pthread_mutex_t lock_write;
} t_info;



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

t_philo	p;

void	stop_eating(t_philo *p, int id, long time);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	init_philo(t_philo *p, char **av, int ac);
long	calculate_time(long	time);
long	get_time();
void	give_forks(t_philo *p, int id, long time);
void	put_to_sleep(t_philo *p, int id);
void	think(t_philo *p, int id);







#endif
