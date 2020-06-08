#include <stdio.h>
#include <math.h>

int main (void) 
{
	float i=0;
    int out=0;
    float highest=-100000;
    float lowest=100000;
    float all=0;
    float mean=0;

	while (out!=EOF)
	{
		out = scanf("%f",&i);
		if (i>highest)
			highest = i;
		if (i<lowest)
			lowest = i;
		if (out!=EOF)
		{
			all = all + 1;
			mean = mean + i;
		}
	}
	printf("%.2f %.2f %.2f\n",lowest, highest, mean/all);

    return 0;
}