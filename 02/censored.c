#include <stdio.h>
#include <string.h>

int findword(char txt[],int loc_1)
{
  for (int loc_2 = loc_1; loc_2 < strlen(txt); loc_2++)
  {
    char a = txt[loc_1];
    char b = txt[loc_2];
    char c = txt[loc_2+1];
    
    if ((a >= 32 && a<=57 && a!=39)||(a >= 58 && a<=63)||a<0||a==10)
      {
        //printf("loc_1 [%d] is not an alpabet, it is %d\n",loc_1, txt[loc_1]);
        return -1;
      }

    if ((c >= 32 && c<=57 && c!=39)||(c >= 58 && c<=63)||c==0||c==10||c==-33)
    {
      if ( (b>=65 && b<=90) || (b>=97 && b<=122)  )
        {
          //printf("found a word between [%d] and [%d], which is %c and %c\n",loc_1,loc_2,txt[loc_1],txt[loc_2]);
          return loc_2;
        }
    }
    if (a==0)
      return -2;

    else
      b=c;
  }
  return 0;
}




int samechar(char txt[],char* censored_word, int loc_1, int loc_2)
{
  int count = 0;
  int loc = loc_1;
  int wordlen = loc_2-loc_1 + 1;

  for (int i=0; i<=strlen(censored_word) ; i++)
  {
    
    if (txt[loc]==censored_word[i])
    {
      //printf("txt [%d] is %d and c[%d] is %d\n",loc,txt[loc],i,censored_word[i]);
      count++;
    }

    loc++;
  }
  
  if ((count == strlen(censored_word) && wordlen == strlen(censored_word))||count-1 == strlen(censored_word))
    {
      //printf("found it!\n\n");
      return 1;
    }
  
  else 
  {
    //printf("No match, length of word is %d and %lu\n\n",wordlen,strlen(censored_word));
    return 0;
  }
}


int censored(char txt[],char* censored_word)
{
  int loc_1 = 0;
  int loc_2 = 0;
  int progress = 0;

  while(txt[progress] != EOF)
  {
    loc_2 = findword(txt, loc_1);

   //printf("#1. loc_1 is %d and loc_2 is %d\n",loc_1, loc_2);

    while (loc_2 == -1 || loc_2 == -2 || loc_2 == 0)
    {
      loc_1++;

      //printf("loc_1 is %d, and it is %d\n",loc_1, txt[loc_1]);
      if (txt[loc_1] == 0)
       {
         //printf("hi");
         return 0;
       }
      loc_2= findword(txt, loc_1);

      if (loc_2==-2)
      {
        //printf("hello");
        return 0;
      }
    }
    //printf("#2. loc_1 is %d and loc_2 is %d\n",loc_1, loc_2);  
    int result = 0;
    result = samechar(txt, censored_word, loc_1, loc_2);

    if (result==1)
    {
      int c=0;

      for(int c = strlen(txt); c >= 1; c--)
      {
        txt[loc_2+c-strlen(censored_word)+8] = txt[loc_2+c];
      }
      
      txt[loc_1+0] = 67;
      txt[loc_1+1] = 69;
      txt[loc_1+2] = 78;
      txt[loc_1+3] = 83;
      txt[loc_1+4] = 79;
      txt[loc_1+5] = 82;
      txt[loc_1+6] = 69;
      txt[loc_1+7] = 68;

      loc_2 = loc_2+8-strlen(censored_word);
  }
    
    loc_1 = loc_2+1;
    progress = loc_1;
  }
  return 0; 
}



int main(int argc,char* argv[]) 
{
  char txt[1000000];
  
  char c;

  int loc = 0;

  while((c=getchar())!=EOF)
  {
    txt[loc]=c;
    loc++;
  }
  


  int i = 1;

  while(i < argc)
  {
    char* censored_word = argv[i];

    censored(txt, censored_word);
   
    i++;
  }
    
  printf("%s",txt);

  return 0;
}

