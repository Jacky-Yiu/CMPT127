#include <stdio.h>
#include "intarr.h"
#include <stdlib.h>
#include <string.h>


/* LAB 6 TASK 1 */

/*
  Save the entire array ia into a file called 'filename' in a binary
  file format that can be loaded by intarr_load_binary(). Returns
  zero on success, or a non-zero error code on failure. Arrays of
  length 0 should produce an output file containing an empty array.

  Make sure you validate the parameters before you use them.
*/

int intarr_save_binary( intarr_t* ia, const char* filename)
{
	
	if(ia==NULL)
		return -1;


	FILE* myfile = fopen(filename,"w");

	if(myfile==NULL)
		return -1;


	if (ia->len > 0)
	{
		intarr_t* save = intarr_copy(ia);

		fwrite(save->data,sizeof(int),ia->len, myfile);
	}

	else
	{
		int zero[]={};
		fwrite(&zero,sizeof(int),0, myfile);
	}


	if(fclose(myfile)!=0)
		return -1;

	return 0;
}

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_binary(). Returns a pointer to a
  newly-allocated intarr_t on success, or NULL on failure.

  Make sure you validate the parameter before you use it.
*/
intarr_t* intarr_load_binary( const char* filename )
{
	
	unsigned int len = 10000;

	intarr_t* load = intarr_create(len);
	if (load == NULL)
		return NULL;

	if(load->len>0)
	{	
		for(int i=0; i < load->len; i++)
		{
			load->data[i]=-1998;
		}
	}

	FILE* myfile = fopen(filename,"r");
	if(myfile==NULL)
		return NULL;

	int count = fread(load->data, sizeof(int), len, myfile);

	fclose(myfile);

	if(count>0)
	{
		for(int i=0;i<load->len;i++)
		{
			if(load->data[i]==-1998)
			{
				intarr_resize( load, i );
				return load;
			}
		}
	}

	else
	{
		intarr_resize(load,0);
		load->len = 0;
	}

	return load;
}

