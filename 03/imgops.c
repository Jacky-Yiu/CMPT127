/*
 * imgops.c - Simple operations on images
 *
 * C laboratory exercises.
 * Richard Vaughan, 2014.
 */

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*-------------------------------------------------
  PART 0: OPERATIONS ON A PIXEL 
*/

// get the value in the array at coordinate (x,y)
uint8_t get_pixel( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows,
           unsigned int x,
           unsigned int y )
{
    assert( x < cols );
    assert( y < rows );
    return array[ y*cols + x ];
}

// set the pixel at coordinate {x,y} to the specified color
void set_pixel( uint8_t array[], 
        unsigned int cols, 
        unsigned int rows,
        unsigned int x,
        unsigned int y,
        uint8_t color )
{
    assert( x < cols );
    assert( y < rows );
    array[ y * cols + x ] = color;
} 


/*-------------------------------------------------
  PART 1: OPERATIONS ON THE WHOLE IMAGE 
*/


/* TASK 1 - Easy functions to get started */

// Set every pixel to 0 (black) 
void zero( uint8_t array[],
	   unsigned int cols,
	   unsigned int rows )
{
  memset(array,0,cols*rows*sizeof(array[0]));
}

// Returns a pointer to a freshly allocated array that contains the
// same values as the original array, or a null pointer if the
// allocation fails. The caller is responsible for freeing the array
// later.
uint8_t* copy( const uint8_t array[], 
           unsigned int cols, 
           unsigned int rows )
{
  uint8_t* new = malloc( cols*rows*sizeof(array[0]));

  for (unsigned int i=0; i<cols*rows; i++)
    new[i] = array [i];

  if (new!=NULL)
    return new;

  return NULL;
}

// Return the darkest color that appears in the array; i.e. the
// smallest value
uint8_t min( const uint8_t array[], 
	     unsigned int cols, 
	     unsigned int rows )
{
  uint8_t min_col = array[0];
  for (unsigned int i=0; i<cols*rows; i++)
  {
    if (array[i] < min_col)
      min_col = array[i];
  }
  return min_col;
}

// Return the lightest color that appears in the array; i.e. the
// largest value
uint8_t max( const uint8_t array[], 
		 unsigned int cols, 
		 unsigned int rows )
{
  uint8_t max_col = array[0];
  for (unsigned int i=0; i<cols*rows; i++)
  {
    if (array[i] > max_col)
      max_col = array[i];
  }
  return max_col;
}

// TASK 2

//  Replace every instance of pre_color with post_color.
void replace_color(  uint8_t array[], 
		     unsigned int cols, 
		     unsigned int rows,
		     uint8_t pre_color,
		     uint8_t post_color )
{
  for (unsigned int i=0; i < cols*rows; i++)
  {
    if (array[i] == pre_color)
      {
        array[i] = post_color;
      }
  }
  return;
}

/* TASK 3  - two functions */


// flip the image, left-to-right, like in a mirror.
void flip_horizontal( uint8_t array[], unsigned int rows,unsigned int cols)
{
  for (unsigned int y = 0; y < cols; y++)
  {
    for (unsigned int x = 0; x < rows; x++)
    {

      unsigned int loc_1 = x +y*rows;
      unsigned int loc_2 = rows-1-x +y*rows;
      
      uint8_t tmp = array[loc_1];

      array[loc_1] = array[loc_2];
      
      array[loc_2] = tmp;

      if (array+loc_1 == array+loc_2||array+loc_1+1 == array+loc_2)
      {
        break;
      }
    }
  } 
}

// flip the image top-to-bottom.
void flip_vertical( uint8_t array[], 
            unsigned int rows, 
            unsigned int cols )
{
  for (unsigned int x = 0; x < rows; x++)
  {
    for (unsigned int y = 0; y < cols; y++)
    {

      unsigned int loc_1 = x+ y*rows;
      unsigned int loc_2 = x+ ((cols-1-y)*rows);
      
      uint8_t tmp = array[loc_1];

      array[loc_1] = array[loc_2];
      
      array[loc_2] = tmp;

      if (array+loc_1 == array+loc_2||array+loc_1+rows == array+loc_2)
      {
        break;
      }
    }
  }
}

/* TASK 4 */

// Find the first coordinate of the first pixel with a value that
// equals color. Search from left-to-right, top-to-bottom. If it is
// found, store the coordinates in *x and *y and return 1. If it is
// not found, return 0.
int locate_color(  const uint8_t array[], 
		   unsigned int cols, 
		   unsigned int rows,
		   uint8_t color,
		   unsigned int *x,
		   unsigned int *y )
{
  for (*y=0; *y < rows; (*y)++)
  {
    for (*x=0; *x < cols; (*x)++)
    {
      if (array[*x+*y*cols]==color)
      {
        return 1;
      }
    }
  }
  return 0;
}

 
/* TASK 5 */

// Invert the image, so that black becomes white and vice versa, and
// light shades of grey become the corresponding dark shade. 
void invert( uint8_t array[], 
         unsigned int cols, 
         unsigned int rows )
{
  for (unsigned int i=0; i < cols*rows; i++)
  {
      array[i] = 255-array[i];
  } 
  return;
}

/* TASK 6 */

// Multiply every pixel by scale_factor, in order to brighten or
// darken the image. Resulting values are rounded to the nearest
// integer (0.5 rounded up) and any resulting value over 255 is
// thresholded to 255.
void scale_brightness( uint8_t array[],
            unsigned int cols,
            unsigned int rows,
            double scale_factor )
{
  for (unsigned int i=0; i < cols*rows; i++)
  {
    double after = array[i]*scale_factor;
    after = round(after);


    if (after < 255)
    array[i] = after;

    else if (after >= 255)
      array[i]=255;
  } 

  return;
}


/* TASK 7 */

// Normalize the dynamic range of the image, i.e. Shift and scale the
// pixel colors so that that darkest pixel is 0 and the lightest pixel
// is 255. Hint: you already wrote min() and max(). 
void normalize( uint8_t array[],
        unsigned int cols,
        unsigned int rows )
{
  double max_col = max(array,cols,rows);
  double min_col = min(array,cols,rows);



  for (unsigned int i=0; i < cols*rows; i++)
    {
      unsigned int a = array[i];

      double scale = (a - min_col)/(max_col - min_col);

      double after = 255*scale;

      array[i] = round(after);
    }
  return;
}

/* TASK 8 */

// Return a new image of size rows/2 by cols/2 If the original image              
// has an odd number of columns, ignore its rightmost column. If the              
// original image has an odd number of rows, ignore its bottom row.               
// The value of a pixel at (p,q) in the new image is the average of               
// the four pixels at (2p,2q), (2p+1,2q), (2p+1,2q+1), (2p,2q+1) in               
// the original image.                                                            
uint8_t* half( const uint8_t array[],
	       unsigned int cols,
	       unsigned int rows )
{
  
  uint8_t * ret = malloc((rows/2)*(cols/2)*sizeof(uint8_t));

  if (ret!=NULL)
  {
    for (unsigned int y = 0; y < rows/2; y++)
      for(unsigned int x = 0; x < cols/2; x++)
      {
        unsigned int total = 0;
        for (unsigned int i = 2*y; i<2*y+2; i++)
          for (unsigned int j = 2*x; j<2*x+2;j++)
            total += array[i*cols+j];

        ret[y*(cols/2)+x]=round(total/4.0);
      }
  }

  return ret;
}




/*-------------------------------------------------
  PART 2: OPERATIONS ON IMAGE SUB-REGIONS

  These functions operate only on a rectangular region of the array
  defined by a (left,top) corner (i.e. closer to the image origin) and
  (right,bottom) corner (i.e. further from the image origin).

  The rectangle edges of a rectangular region are aligned with the x,y axes. 
  
  The region includes all the columns from [left, right-1] inclusive,
  and all the rows from [top, bottom-1] inclusive.
  
  In every case, you may assume that left <= right and top <= bottom:
  do not need to test for this.

  The area of the region is right-left * bottom-top pixels, which
  implies that if left == right or top == bottom, the region has no
  area and is defined as "empty". Each function notes how to handle
  empty regions.
 
  In every function, you can use assert() to test bounds on the region
  corners.
*/

/* TASK 9 */

// Set every pixel in the region to color. If the region is empty, the
// image must remained unchanged.
void region_set( uint8_t array[], 
         unsigned int cols, 
         unsigned int rows,
         unsigned int left,
         unsigned int top,
         unsigned int right,
         unsigned int bottom,
         uint8_t color )
{
  if (top != bottom && left!=right)
  {
    for (unsigned int y=0; y < rows; y++)
    {
      for (unsigned int x=0; x < cols; x++)
      {
        if (x >= left && x<= right-1 && y >= top && y<= bottom-1)
          array[x+y*cols]=color;
      }
    }
  }
  return;
}

/* TASK 10 */

// Return the sum of all the pixels in the region. Notice the large
// return type to handle potentially large numbers. Empty regions
// return the sum 0.
unsigned long int region_integrate( const uint8_t array[], 
                    unsigned int cols, 
                    unsigned int rows,
                    unsigned int left,
                    unsigned int top,
                    unsigned int right,
                    unsigned int bottom )
{
  unsigned long int sum = 0;
  if (top != bottom && left!=right)
  {
    for (unsigned int y=0; y < rows; y++)
    {
      for (unsigned int x=0; x < cols; x++)
      {
        if (x >= left && x<= right-1 && y >= top && y<= bottom-1)
          sum++;
      }
    }
  }
  return sum;
}

/* TASK 11 */

// Get a new image which is a copy of the region. Empty regions return
// a null pointer. If memory allocation fails, return a null
// pointer. The caller is responsible for freeing the returned array
// later.
uint8_t* region_copy( const uint8_t array[], 
              unsigned int cols, 
              unsigned int rows,
              unsigned int left,
              unsigned int top,
              unsigned int right,
              unsigned int bottom )
{
  
  unsigned int size = (right-left) * (bottom-top);

  uint8_t * new = malloc(size * sizeof(uint8_t));

  for( unsigned int i = 0; i < size; i++ )
    new[i] = 0; 

  if (top == bottom || left == right)
  {
    new = NULL;
    return new;
  }
 
  unsigned int i = 0;

  while (i < size)
  {
    for (unsigned int y=0; y < rows; y++)
    {
      for (unsigned int x=0; x < cols; x++)
      {
        if (x >= left && x<= right-1 && y >= top && y<= bottom-1)
        {
          new[i] = array[x+y*cols];
          i++;
          if (i>=size)
            return new;
        }
      }
    }
  }
  return new;
}


