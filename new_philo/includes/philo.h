#ifndef PHILO_H
# define PHILO_H

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

typedef enum s_state
{
	scratch_balls,
	eating,
	sleeping,
	think,
	died
}	t_state;

typedef struct s_argv
{
	int	ac;
	int	nbr;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_times_to_eat;
}	t_argv;

typedef struct s_philo
{
	int			id;
	pthread_t	t;
	t_state		st;
	bool		*fork_left;
	bool		*fork_right;
}	t_philo;

typedef struct s_m
{
	t_philo		*philo;
	bool		*forks;
}	t_m;

typedef struct s_mutex
{
	pthread_mutex_t	lock;
	pthread_mutex_t	lock2;
	pthread_mutex_t	print;
} t_mutex;

t_mutex	mutex;
t_argv	args;

void	init_master(t_m *master);
void	init_argv(char **av, int ac);
void	received_argv(t_m *master);

#endif