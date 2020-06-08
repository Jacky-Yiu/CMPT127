#include<stdio.h>
void reverse( int arr[], unsigned int len)
{
	for (int i=0;i<len/2;i++)	
	{
		int temp_num = *(arr+i);

		*(arr+i) = *(arr+len-1-i);

    *(arr+len-1-i) = temp_num;
	}			
}