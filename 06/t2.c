#include <stdio.h>
#include "intarr.h"
#include <stdlib.h>

/* LAB 6 TASK 2 */

/*
  Save the entire array ia into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  intarr_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.

  Make sure you validate the parameters before you use them.
  
  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON array:
  [ 100, 200, 300 ]
  
  The following lines are a valid JSON array:
  [ 
   100, 
   200, 
   300 
  ]
*/
int intarr_save_json( intarr_t* ia, const char* filename )
{
	if(ia==NULL)
    return -1;

  FILE* myfile = fopen(filename,"w+");

  if(myfile==NULL)
    return -1;

  fprintf(myfile, "[");

  for (int i=0; i < ia->len; i++)
  {
    if  (i==0)
      fprintf(myfile, " %d", ia->data[i]);
    else
      fprintf(myfile, ", %d", ia->data[i]);     
  }

  fprintf(myfile, " ]\n");

  fclose(myfile);  
  return 0;
}


/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_json(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.

  Make sure you validate the parameter before you use it.
*/
intarr_t* intarr_load_json( const char* filename )
{
	intarr_t* load = intarr_create(10000);

  if (load == NULL)
    return NULL;

  for(int i=0;i<load->len;i++)
  {
    load->data[i]=-1998;
  }

  FILE* myfile = fopen(filename,"r");
  if(myfile==NULL)
    return NULL;

  int loc = 0;

  int start = fscanf(myfile,"[ %d",&load->data[loc]);
  if (start==0)
  {
    intarr_resize(load,0);
    load->len = 0;
    return load;
  }

  loc++;
  while(fscanf(myfile,", %d",&load->data[loc])==1)
  {
    loc++;
  }

  fscanf(myfile,", %d ]",&load->data[loc]);

  fclose(myfile);

  for(int i=0;i<load->len;i++)
  {
    if(load->data[i]==-1998)
      intarr_resize( load, i );
  }


  return load;
}