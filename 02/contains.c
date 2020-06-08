#include <stdio.h>
#include <string.h>
int contains(char* a, char* b)
{
	char* result = strstr(a, b);
	
	if (result== NULL)
		printf("false\n");
	else
		printf("true\n");

	return 0;
}

int main(int argc, char* argv[])
{
	char* a = argv[1];
	char* b = argv[2];
	contains(a, b);
	return 0;
}