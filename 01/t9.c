#include <stdio.h>
#include <math.h>

int printx (int x)
{
  int a;
  if (x!=0)
  {
    for (a=0;a<x;a++)
    {
      printf(" ");
    }
  }
  printf("#");
  return 0;
}



int printdot (int x)
{
  int a;
  if (x!=0)
  {
    for (a=0;a<x;a++)
    {
      printf(".");
    }
  }
  printf("#");
  return 0;
}



int hashtag (int i)
{
  while (i!=0)
  {
    printf("#");
    i=i-1;
  }
  return 0;
}



int main (void) 
{
  int x=0;
  int y=0;
  int z=0;
  int Rxi=0;
  int Lxi=0;
  int zi=0;

  scanf("%d %d %d",&x,&y,&z);
  

  for (zi=z-1;zi>=0;--zi)
  {
    Lxi = floor( zi * (x/(2.0*z)) );
    Rxi = ceil( (x-1) + -zi * (x/(2.0*z)) );


    if (zi==0)
    {
      printf("#");
      hashtag(Rxi-(Lxi));
    }


    else if (zi==z-1)
    {
      if(zi!=0)
      {
        printx(Lxi);
        hashtag(Rxi-(Lxi));
      }
    }


    else
    {
    printx(Lxi);
    printdot(Rxi-(Lxi+1));
    }
    printf("\n");
  }


  return 0;
}