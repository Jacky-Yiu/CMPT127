#include <stdio.h>

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

int dot (int x)
{
  printf("#");
  int b=0;
  while (b!=x-2)
  {
    printf(".");
    b=b+1;
  }
  printf("#");
  printf("\n");
}


int main (void) 
{
	int x=0;
  int y=0;
  int z=0;
  int c=0;
  scanf("%d %d %d",&x,&y,&z);
  
  hashtag(x);

  if (y>=2){
  while (c!=y-2)
  {
    dot(x);
    c=c+1;
  }
  hashtag (x);
  }
  return 0;
}