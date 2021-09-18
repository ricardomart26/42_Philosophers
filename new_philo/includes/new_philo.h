#ifndef NEW_PHILO_H
# define NEW_PHILO_H

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

typedef enum s_state
{
	scratch_balls,
	eating,
	sleep,
	think,
	is_dead
}	t_state;


typedef

typedef struct s_info
{
	long	time_to_eat;
	long	time_to_sleep;
	long	time_to_die;
	long	last_eat;
	int		counter_eat;
	int		how_many_times_to_eat;
}	t_info;

typedef struct s_argv
{
	int		ac;
	int		nbr;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nbr_times_to_eat;
}	t_argv;

typedef struct s_philo
{
	int id;
	pthread_t t;
	t_state st;
	t_info info;
	bool *fork_left;
	bool *fork_right;

}	t_philo;


typedef struct s_m
{
	t_philo *philo;
	bool *forks;
}	t_m;


#endif