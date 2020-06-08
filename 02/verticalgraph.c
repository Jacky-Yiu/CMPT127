#include <stdio.h>

int find_max(int num[])
{ 
  int max = num[0];

  for(int i=1; i<=80; i++)
  {
    if (num[i] > max)
      max = num[i];
  }
  return max;
}

int graph(int num[],int len, int max)
{
  for (int floor = max; floor > 0; floor--)
  {
    for (int lenght = 0; lenght <= len; lenght++)
    {  
      if (num[lenght] < floor && num[lenght]>=0)
      printf(" ");

      if (num[lenght]>=floor)
        printf("#");

      if (num[lenght]==-1)
        {
          printf("\n");
        }
    }
  }  
  return 0;
}




int main(void) 
{
  int i;
  int num[80];
  for(i=0; i<=80; i++)
  {
    num[i]=0;
  }

  int len=0;
  
  while (( scanf("%d",&num[len])!=EOF && len<80))
  {
    len++;
  }
  num[len] = -1;

  int max= find_max(num);

  graph(num, len, max);

  return 0;
}
