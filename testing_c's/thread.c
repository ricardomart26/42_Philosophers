#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void	*my_turn()
{
	while (1)
	{
		sleep(2);
		printf("My turn!\n");
	}
}

void	*your_turn()
{
	while (1)
	{
		sleep(2);
		printf("Your turn!\n");
	}
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;

	pthread_create(&thread1, NULL, my_turn, NULL);
	pthread_create(&thread2, NULL, your_turn, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}