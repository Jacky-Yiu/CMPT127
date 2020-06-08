#include <stdio.h>

int identical(int arr[], int arr2[], unsigned int len)
{
	if (len==0)
		return 1;

	int same_num = 0;

	for (int num = 0; num < len; num++)
	{
		if (arr[num]==arr2[num])
			same_num++;
	}

	if (same_num == len)
		return 1;
	else
		return 0;
}