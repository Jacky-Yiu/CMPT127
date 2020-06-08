#include <stdio.h>
#include <math.h>

int main (void) 
{
	float i;
    int out;
	out = scanf("%f",&i);
	
	if(out==0)
		printf("scanf error: (%d)\n",out);
		
	else
		printf("%d %d %d\n",(int)floor(i),(int)round(i),(int)ceil(i));
    return 0;
}