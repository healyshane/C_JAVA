#include <stdio.h>

int main()
{
	char name[20];

	printf("What is your name?");

	fgets(name, 20,stdin);

	printf("Hello %s", name);

	return 0;
}


#include <stdio.h>

int main()
{
	printf("Hello, World\n");
	return 0;
}
