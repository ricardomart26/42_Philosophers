#include "philo.h"

long	get_time()
{
	long time;
	struct timeval t;

	gettimeofday(&t, NULL);
	time = (t.tv_sec * 1000) + (t.tv_usec/1000);
	return (time);
}

long	calculate_time(long	time)
{
	long time2;
	long diff;

	time2 = get_time();
	diff = time2 - time;
	return (diff);
}

