#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "image2.hpp"
#include <string.h>

Image::Image()
  : cols(0),   // initialization list 
    rows(0), 
    pixels(NULL) 
{
   // No work to do in constructor body in this example: 
   // the intialization list took care of it. 
   // All  members now have safe initial values.
}

Image::~Image()
{
   // free everything that could have been allocated inside this object
   if( pixels != NULL ) 
   {
      delete[] pixels; 
   }
}
/* Sets the colour of the pixel at (x,y) to colour. Returns 0 on success, else a non-zero 
     error code. If (x,y) is not a valid pixel, the call fails and the image does not change.*/
int Image::set_pixel( unsigned int x, unsigned int y, uint8_t colour )
{
  // x, y, and colour are local variables
  // pixels and cols are members of this object
  // so can be accessed through the 'this' pointer
  if(x>cols||y>rows||pixels==NULL)
    return 1;


  pixels[ y * cols + x ] = colour; 
  return 0;
}

 /* Gets the colour of the pixel at (x,y) and stores at the address pointed to 
     by colourp. Returns 0 on success, else a non-zero error code. */
 int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colourp )
 {
    if(x>cols||y>rows||pixels==NULL||colourp==NULL)
    return 1;
  
    *colourp=pixels[ y*cols + x ];
    return 0;
 }

/* Changes the size of an image, allocating memory as necessary, and
     setting all pixels to fillcolour. Returns 0 on success, or a non-zero error code.*/ 
int Image::resize(unsigned int width,  unsigned int height, uint8_t fillcolour)
{

  rows=height;
  cols=width;
  pixels = (uint8_t*)realloc( pixels, cols*rows*sizeof(uint8_t));


  for( unsigned int y=0; y<rows; y++ ) 
    for( unsigned int x=0; x<cols; x++ ) 
      set_pixel( x, y, fillcolour );
      
   return 0;
}


  /* Saves the image in the file filename. In a format that can be
     loaded by load(). Returns 0 on success, else a non-zero error
     code. */
int Image::save( const char* filename )
{

  FILE* myfile = fopen(filename,"w");

  if(myfile==NULL)
    return -1;

  if (rows==0||cols==0)
  {
    fprintf(myfile, "[ 0, 0, 0]");
  }

  fprintf(myfile, "[ %u, %u,",cols,rows);

  for (unsigned int i=0; i < (cols*rows); i++)
  {
    if  (i==0)
      fprintf(myfile, " %d", (int)pixels[i]);
    else
      fprintf(myfile, ", %d", (int)pixels[i]);     
  }

  fprintf(myfile, " ]\n");

  if(fclose(myfile)!=0)
    return -1;

  return 0;
  }

  /* Load the an image from the file filename, replacing the current
     image size and data. The file is in a format that was saved by
     save(). Returns 0 success, else a non-zero error code . */
int Image::load( const char* filename )
{

  unsigned int load_list[1000000];

  FILE* myfile = fopen(filename,"r");

  if(myfile==NULL)
    return -1;

  int loc = 0;

  int start = fscanf(myfile,"[ %u, %u",&load_list[loc],&load_list[loc+1]);
  if (start==0)
  {
    return -1;
  }

  loc++;
  loc++;

  while(fscanf(myfile,", %d",&load_list[loc])==1)
  {
    loc++;
  }

  fscanf(myfile,", %d ]",&load_list[loc]);

  fclose(myfile);


  resize((unsigned int)load_list[0], (unsigned int)load_list[1], 1);

  if(rows!=0&&cols!=0)
  {
    for(unsigned int i = 0; i<rows*cols; i++)
    {
      pixels[i]= (uint8_t)load_list[i+2];
    }
  }

  return 0;
}