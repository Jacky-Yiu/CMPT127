#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "point_array.h"

// Safely initalize an empty array structure.
void point_array_init( point_array_t* pa )
{
	if (pa == NULL)
		return;
	pa->len=0;
	pa->points=NULL;
	pa->reserved=10;
}

// Resets the array to be empty, freeing any memory allocated if necessary.
void point_array_reset( point_array_t* pa )
{
	if (pa==NULL)
		return;
	pa->len=0;
	if(pa->points != NULL)
		free(pa->points);
}

// Append a point to the end of an array. If successful, return 0, else return 1.
int point_array_append( point_array_t* pa, point_t* p )
{
	if (pa==NULL||p==NULL)
		return 1;

	if (pa->len==0)//if the list is empty
	{
		pa->len = 1;

		pa->points=(point_t*)realloc(pa->points,pa->reserved*sizeof(point_t));

		if(pa->points==NULL)
			return 1;

		*(pa->points) = *p;
	}

	else if (pa->len == pa->reserved) // if the list is full
	{
		(pa->reserved) = (pa->reserved)*2; // double the reserved

		pa->points=(point_t*)realloc(pa->points,pa->reserved*sizeof(point_t)); //realloc using new reserved
		
		if(pa->points==NULL)
			return 1;
		
		pa->len++; //increse len by 1

		*((pa->points)+(pa->len)-1) = *p; // set lest element
	}

	else // if the list have element but not full
	{
		pa->len++; //increase len by 
		
		*((pa->points)+(pa->len)-1) = *p; //set last element		
	}

	return 0;
}

// Remove the point at index i from the array, reducing the number of elements
// stored in the array by one. The order of points in the array may change.
// If successful, return 0, else return 1. 
int point_array_remove( point_array_t* pa, unsigned int i )
{
	if (pa==NULL)
		return 1;

	if(pa->len==0)
		return 1;

	if (i>=pa->len)
		return 1;


	if(i < pa->len)
	{

		*((pa->points)+i) = *((pa->points)+(pa->len)-1);
	}

	pa->len--;

	//pa->points=(point_t*)realloc(pa->points,pa->len*sizeof(point_t));

	if (pa->points==NULL)
		return 1;

	return 0;
}
