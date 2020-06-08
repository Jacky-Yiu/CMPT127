#include <stdio.h>
#include <math.h>

int hashtag(int x) 
{
  int a=0;
  while (a!=x)
  {
    printf("#");
    a=a+1;
  }
  printf("\n");
}


int main (void) 
{
	float i=0;
  int out=0;
	while (out!= EOF)
  {
		out=scanf("%f",&i);
		if(out==EOF)
			break;
		hashtag(i);
  }
return 0;
}