#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Race condition
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
uint32_t counter = 0;

void	*funct()
{
	int32_t i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&lock);
		i++;
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

void	*funct2()
{
	int32_t i = 0;
	while (i < 10000000)
	{
		pthread_mutex_lock(&lock);
		i++;
		counter++;
		pthread_mutex_unlock(&lock);
	}
	return (NULL);
}

int main(void)
{
	pthread_t thread1;
	// pthread_t thread2;
	int i = 0;

	pthread_create(&thread1, NULL, funct, NULL);
	// pthread_create(&thread2, NULL, funct2, &i);
	funct();
	pthread_join(thread1, NULL);

	// pthread_join(thread2, NULL);
	printf("3: counter = %d\n", counter);
}