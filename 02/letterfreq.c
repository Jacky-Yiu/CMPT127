#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_same(char txt[],char alphabet)
{
  int count=0;
  for(int i=0; i<strlen(txt);i++)
  {
    if (txt[i] == alphabet || txt[i] == alphabet-32)
      count++;
  }
  return count;
}

int all_letter(char txt[])
{
  int letter_count = 0;
  for(int i=0; i<strlen(txt);i++)
  {
    if ( (txt[i]>=65 && txt[i]<=90) || (txt[i]>=97 && txt[i]<=122)  )
      letter_count++;
  }
  return letter_count;
}

int main(void) 
{
  
  double all_let = 0;

  double letter_sum [26];
  for (int i=0; i<26; i++)
    letter_sum[i] = 0;
  
  char letter [26];
  for (int i=0; i<26; i++)
    letter[i] = 97+i;


  char txt[1000000];
  int loc = 0;
  char c;

  while ((c = getchar()) != EOF)
  	{
  		txt[loc]=c;
  		loc++;
  	}
  
  all_let += all_letter(txt); 

  for(int i = 0; i <26 ;i++)
  	letter_sum[i] += count_same(txt, letter[i]);
  
  double freq[26];
  
  for(int i = 0; i <26 ;i++)
  {
    freq[i] = letter_sum[i]/all_let;

    if (letter_sum[i]!=0)
      printf( "%c %.4f\n", letter[i], freq[i]);
  }

  return 0;
}
