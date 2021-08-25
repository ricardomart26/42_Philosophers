void				ft_putnbr(unsigned long long n)
{
	char	c;

	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

void				msg(unsigned long long time, int act, char *text, int len)
{
	pthread_mutex_lock(&g_data.write);
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(act + 1);
	write(1, text, len);
	pthread_mutex_unlock(&g_data.write);
}

unsigned long long	thread_lockfork(int act, int prev)
{
	unsigned long long	time;

	pthread_mutex_lock(&g_data.lock);
	pthread_mutex_lock(&g_data.philo[prev].lock);
	time = gettime();
	msg(time, act, " has taken a fork\n", 18);
	pthread_mutex_lock(&g_data.philo[act].lock);
	time = gettime();
	msg(time, act, " has taken a fork\n", 18);
	pthread_mutex_unlock(&g_data.lock);
	return (time);
}

void				*thread(void *arg)
{
	int					act;
	int					prev;
	unsigned long long	time;

	act = *(int*)arg;
	prev = act - 1;
	if (prev == -1)
		prev = g_data.nb - 1;
	time = thread_lockfork(act, prev);
	g_data.philo[act].last_eat = time;
	msg(time, act, " is eating\n", 11);
	usleep(g_data.time_eat * 1000);
	time = gettime();
	g_data.philo[act].total_eat += g_data.time_eat;
	msg(time, act, " is sleeping\n", 13);
	pthread_mutex_unlock(&g_data.philo[prev].lock);
	pthread_mutex_unlock(&g_data.philo[act].lock);
	usleep((g_data.time_sleep - (time - g_data.philo[act].last_eat -
												g_data.time_eat)) * 1000);
	time = gettime();
	msg(time, act, " is thinking\n", 13);
	if (g_data.state == 1)
		thread(arg);
	return (0);
}
