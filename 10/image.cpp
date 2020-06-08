#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "image.hpp"

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
  if(x>=cols||y>=rows||pixels==NULL)
  	return 1;


  this->pixels[ y * this->cols + x ] = colour; 
  return 0;
}

 /* Gets the colour of the pixel at (x,y) and stores at the address pointed to 
     by colourp. Returns 0 on success, else a non-zero error code. */
 int Image::get_pixel( unsigned int x, unsigned int y, uint8_t* colourp )
 {
    if(x>=cols||y>=rows||pixels==NULL||colourp==NULL)
  	return 1;
  
    *colourp=this->pixels[ y*this->cols + x ];
    return 0;
 }

/* Changes the size of an image, allocating memory as necessary, and
     setting all pixels to fillcolour. Returns 0 on success, or a non-zero error code.*/ 
int Image::resize(unsigned int width,  unsigned int height, uint8_t fillcolour)
{

  rows=height;
  cols=width;
  pixels = (uint8_t*)realloc( pixels, cols*rows*sizeof(uint8_t));


  for( int y=0; y<rows; y++ ) 
  	for( int x=0; x<cols; x++ ) 
     	set_pixel( x, y, fillcolour );
      
   return 0;
}


