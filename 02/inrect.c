#include <stdio.h>
int InRectangle( float pt[2], float rect[4])
{
  float minx= rect[0];
  float maxx= rect[2];
  if (rect[0]>rect[2])
  {
    minx= rect[2];
    maxx= rect[0];
  }

  float miny= rect[1];
  float maxy= rect[3];
  if (rect[1]>rect[3])
  {
    miny= rect[3];
    maxy= rect[1];
  }
  
  float x_corr = pt[0];
  float y_corr = pt[1];

  
  if (x_corr <= maxx && x_corr >= minx)
  {  
    if (y_corr <= maxy && y_corr >= miny)  
      return 1;
  }

  return 0;
}
