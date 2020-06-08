#include <stdio.h>
#include <math.h>

int main (void) 
{
	float i=0;
    int out=0;
	while (out!= EOF){
		out=scanf("%f",&i);
		if(out==EOF)
			break;
		printf("%d %d %d\n",(int)floor(i),(int)round(i),(int)ceil(i));
	}
	printf("Done.\n");
    return 0;
}
