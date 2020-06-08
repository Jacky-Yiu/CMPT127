#include <stdio.h>
int scrambled( unsigned int arr1[], unsigned int arr2[], unsigned int len )
{
	int same_num = 0;
	for (int i=0;i<len;i++)
	{
      if (arr1[i] == arr2[i])
      {
        same_num++;
        arr2[i]=100;
        arr1[i]=101;
      }

      for (int a = i+1; a < len ;a++)
        {
        	if (arr1[i]==arr2[a])
        		{
              same_num++;
              arr2[a]=100;
              arr1[i]=101;
            }
        }

       for (int a=i-1;a >= 0 ;a--)
       	{
        	if (arr1[i]==arr2[a])
        		{
              same_num++;
              arr2[a]=100;
              arr1[i]=101;
            }
        }
    }
    if (same_num==len)
  		return 1;
  	else
      return 0;
}	