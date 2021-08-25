#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	struct timeval time;
	struct timeval end;
	long seconds;
	long useconds;
	long timediff;
	gettimeofday(&time, NULL);
	// sleep(60);
	gettimeofday(&end, NULL);
	seconds = (end.tv_sec - time.tv_sec);
	useconds = (end.tv_usec - time.tv_usec);
	timediff = (seconds * 1000) + (useconds/1000);
	printf("time sec %ld e time ms %ld diff %ld\n", seconds, useconds, timediff);
	
	return (0);
}