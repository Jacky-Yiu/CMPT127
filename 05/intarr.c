#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "intarr.h"
/* LAB 5 TASK 1 */

// Create a new intarr_t with initial size len.  If successful
// (i.e. memory allocation succeeds), returns a pointer to a
// newly-allocated intarr_t.  If unsuccessful, returns a null pointer.
intarr_t* intarr_create( unsigned int len )
{
	intarr_t* new = (intarr_t*) malloc(sizeof(intarr_t));
	if (new == NULL)
    	return NULL;

	new->data = (int*) malloc(len*sizeof(int));
	new->len = len;

	return new;
}

// Frees all memory allocated for ia. If the pointer is null, do
// nothing. If the ia->data is null, do not attempt to free it.
void intarr_destroy( intarr_t* ia )
{
	if (ia == NULL || ia->data == NULL)
		return;

	free(ia->data);
	free(ia);
}

/* LAB 5 TASK 2 */

// If index is valid, set the value at ia->data[index] to val and return
// INTARR_OK. Otherwise, leave the array unmodified and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_set( intarr_t* ia, 
							unsigned int index, 
							int val )
{
	if (ia == NULL)
		return INTARR_BADARRAY;

	if (index >= ia->len)
		return INTARR_BADINDEX;

	if (index < ia->len)
		ia->data[index] = val;

	return INTARR_OK;
}

// If index is valid and val is non-null, set *val to ia->data[index] and return
// INTARR_OK. Otherwise do not modify *val and return
// INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_get( const intarr_t* ia, 
							unsigned int index, 
							int* val )
{
	if (ia == NULL)
		return INTARR_BADARRAY;

	if (index >= ia->len)
		return INTARR_BADINDEX;

	if (index < ia->len && val != NULL)
		*val= ia->data[index];

	return 0;
}

/* LAB 5 TASK 3 */

// Return a duplicate of ia, allocating new storage for the duplicate
// data (we call this a "deep copy"). If unsuccessful (i.e. memory
// allocation for the copy fails, or ia is null), return a null pointer. 
intarr_t* intarr_copy( const intarr_t* ia )
{
	if (ia == NULL)
    	return NULL;

	intarr_t* copy = (intarr_t*) malloc(sizeof(intarr_t));
	if (copy == NULL)
    	return NULL;

    copy->data = ia->data;
    copy->len = ia->len;
    
    unsigned int numbytes = copy->len*sizeof(int);
    copy->data = malloc(numbytes);

    memcpy( copy->data, ia->data, numbytes );

	return copy;
}

/* LAB 5 TASK 4 */

// Sort ia by value smallest-to-largest, so that data[i] < data[i+1]
// for all valid i, then return INTARR_OK. Works in-place: contents of
// ia are sorted on return. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_sort( intarr_t* ia )
{
	if (ia == NULL)
    	return INTARR_BADARRAY;
    
    for (int i=0;i < (ia->len);i++)
    {	
    	int min = ia->data[i];
    	int min_index = i;

    	for (int j=i+1;j < (ia->len);j++)
    	{
    		if (ia->data[j] < min)
    		{
    			int temp = ia->data[min_index];
    			ia->data[min_index] = ia->data[j];
    			ia->data[j] = temp;

    			min = ia->data[i];
    			min_index = i;
    		}
    	}
    }	

	return INTARR_OK;
}

/* LAB 5 TASK 5 */

// Find the first occurrence of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i )
{
	if (ia == NULL)
    	return INTARR_BADARRAY;

    for (int j=0;j < (ia->len);j++)
    {
    	if(ia->data[j] == target)
    		{
    			*i = j;
    			return INTARR_OK;
    		}
    }

    return INTARR_NOTFOUND;
}

/* LAB 5 TASK 6 */

// HINT: First, do TASK 7, since you will need to resize your array
//       by +1 in order to successfully push val.
// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val )
{
	if (ia == NULL)
    	return INTARR_BADARRAY;

	int result = intarr_resize(ia,(ia->len)+1);

	if (result == INTARR_BADALLOC)
    	return INTARR_BADALLOC;

    ia->data[ia->len-1] = val;


	return INTARR_OK;
}

// HINT: You will need to decrement len so that it always represents
//       the number of int's stored in the array data.
// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i )
{
	if (ia == NULL)
    	return INTARR_BADARRAY;
    
    if (ia->data == NULL || ia->len <= 0|| i == NULL)
    	return INTARR_BADINDEX;

    
    else if(ia->len > 1)
    {
    	*i = (ia->data)[(ia->len)-1];

		int result = intarr_resize(ia,(ia->len)-1);

		if (result == INTARR_BADALLOC)
			return INTARR_BADALLOC;
    }

    else
    {
    	*i = (ia->data)[(ia->len)-1];

		intarr_resize(ia,(ia->len)-1);

		ia->len=0;
    }
 
	return INTARR_OK;
}

/* LAB 5 TASK 7 */

// HINT: Do this task before doing TASK 6.
// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. 
// If newlen is greater than the original array length, the values 
// of the new integers will be undefined 
// (see https://en.cppreference.com/w/c/memory/realloc). 
// If the allocation is successful, return INTARR_OK, otherwise 
// return INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen )
{
	if (ia == NULL)
    	return INTARR_BADARRAY;

	ia->data = (int*)realloc(ia->data,newlen*sizeof(int));

	if (ia->data == NULL)
    	return INTARR_BADALLOC;

	ia->len = newlen;
	
	return INTARR_OK;
}

/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index 'first' to index 'last'
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, 'first' or 'last' are out of bounds, 
// 'last' < 'first', or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, 
								unsigned int first, 
								unsigned int last )
{
	if (ia == NULL|| last<first || first >= ia->len||last >= ia->len) 
	return NULL;

	intarr_t* copy = (intarr_t*) malloc(sizeof(intarr_t));

	if (copy == NULL)
    	return NULL;

    copy->len = last-first+1;
    
    copy->data = (int*)malloc((copy->len)*sizeof(int));

    for (int i = 0; i<copy->len; i++)
    {
    	copy->data[i] = ia->data[first+i];
    }

	return copy;
}