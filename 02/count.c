#include <stdio.h>
int count(void)
{
  unsigned long int charcount = 0;
  unsigned long int wordcount = 0;
  unsigned long int linecount = 0;
  int c;
  int d = 0;
  while ((c=getchar()) != EOF)
  {
    charcount++;

    // if input a space, sign or new line
    if ((c >= 32 && c<=47 && c!=39)||(c >= 58 && c<=63)||c==10)
    {
      // if pervious charater is an alphabet
      if ( (d>=65 && d<=90) || (d>=97 && d<=122)  )
        wordcount++;
    }

    if (c==10)
      linecount++;
      
    d = c;
  }
  printf( "%lu %lu %lu\n", charcount, wordcount, linecount );
  return 0;
}

int main()
{
  count();
  return 0;
}
