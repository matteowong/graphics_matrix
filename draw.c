#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
}




void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  //swap x0,y0 and x1,y1 if necessary
  if (x0>x1) {
    //printf("swap\n");
    int temp=x0;
    x0=x1;
    x1=temp;
    temp=y0;
    y0=y1;
    y1=temp;
  }else if (x0==x1 && y0>y1) {
    int temp=y0;
    y0=y1;
    y1=temp;
  }
  
  //int oct=which_oct(x0,y0,x1,y1);
  //printf("which_oct: %d\n",oct);

  int x,y,A,B,d;
  x=x0;
  y=y0;
  A=y1-y0;
  B=-(x1-x0);

  if (A*B<=0) {//positive slope octant 1
    if (abs(A)<=abs(B)) {
      d=2*A+B;
      while (x<=x1) {
	plot(s,c,x,y);
	if (d>0) {
	  y++;
	  d+=2*B;
	}
	x++;
	d+=2*A;
      }
    }

    else if (abs(A)>abs(B)) {
      d=A+2*B;
      while(y<=y1) {
	plot(s,c,x,y);
	if (d<0) {
	  x++;
	  d+=2*A;
	}
	y++;
	d+=2*B;
      }
    }
  }
  else {
    if (abs(A)<=abs(B)) {
      //octant 8, -1<m<0
  
      d=2*A-B;
      while (x<=x1) {
	plot(s,c,x,y);
	if (d<0) {
	  y--;
	  d-=2*B;
	}
	x++;
	d+=2*A;
      }
    }
    else if (abs(A)>abs(B)) {
      //octant 7, m<-1
      d=A-2*B;
      while (y>=y1) {
	plot(s,c,x,y);
	if (d>0) {
	  x++;
	  d+=2*A;
	}
	y--;
	d-=2*B;
      }
    }
  }
  /*else if (oct==-1) {
    if (y>y1) {
    y0=y1;
    y1=y;
    y=y0;
    }
    while (y<=y1) {
    plot(s,c,x,y);
    y++;
    }
    }*/
}

