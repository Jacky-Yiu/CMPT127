#include <stdio.h>
#include <math.h>

int main (void) 
{
	float i;

	scanf("%f",&i);
	printf("%d %d %d\n",(int)floor(i),(int)round(i),(int)ceil(i));

	return 0;
}