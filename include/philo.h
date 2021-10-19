/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimartin <rimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 23:11:21 by rimartin          #+#    #+#             */
/*   Updated: 2021/10/19 18:39:49 by rimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>

# define THREAD_LIMIT 200
# define MSG_MAX 4

static struct timeval	g_start_time;
static pthread_mutex_t	g_lock;
static pthread_mutex_t	g_lock_write;
static t_args			g_args;

typedef enum s_state
{
	scratch_balls,
	eating,
	sleeping,
	thinking,
	is_dead
}	t_state;

typedef struct s_info
{
	int				id;
	pthread_t		t;
	bool			*fork_left;
	bool			*fork_rigth;
	t_state			st;
	long			started_eating;
	long			started_sleeping;
	int				c_eat;
	pthread_mutex_t	*left_fork_m;
	pthread_mutex_t	*rigth_fork_m;
}	t_info;

typedef struct s_args
{
	int	total_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	how_many_times_to_eat;
	int	time_to_eat;
	int	nbr_philo;
	int	kill;
	int	full;
}	t_args;

typedef struct s_philo
{
	t_info			*philo;
	bool			*forks;
	pthread_mutex_t	*forks_m;
}	t_philo;

t_info	*unlock_eve(t_info *p);
void	printer(int id, t_state state);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		stop_eating(t_info *p);
void	init_philo(t_philo *p);
void	init_args(int ac, char **av);
long	calculate_time(long time);
long	get_time(void);
int		give_forks(t_info *p);
int		check_death_while_sleeping(t_info *p);
int		check_death_while_eating(t_info *p);
int		check_death(t_info *p);

#endif
