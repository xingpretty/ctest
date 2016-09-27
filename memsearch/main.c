#include<stdio.h>
#include<stdlib.h>

int main()
{
	int a = 299;
	while(1)
	{
		printf("%d",a);
		sleep(2);
		fflush(stdout);
	}
	return 0;
}
