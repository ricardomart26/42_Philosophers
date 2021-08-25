#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	*my_turn(void *ptr)
{
	int *iptr = malloc(sizeof(int *));
	for (; *iptr < 10; (*iptr)++)
	{
		sleep(1);
		printf("My turn\n");
	}
	return ((void *)iptr);
}

int main(void)
{
	pthread_t newthread;
	int *ret;

	pthread_create(&newthread, NULL, my_turn, NULL);

	pthread_join(newthread, (void *)&ret);
	printf("v %d\n", *ret);
}