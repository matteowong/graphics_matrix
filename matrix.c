#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*
int main() {

  struct matrix * m=new_matrix(4,4);
  struct matrix * n=new_matrix(4,3);
  m->lastcol=4;
  n->lastcol=3;
  

  printf("\ntesting ident(m)\n");
  ident(m);
  print_matrix(m);

  n->m[0][0]=4;
  n->m[0][1]=37;
  n->m[3][2]=9;
  n->m[2][2]=10;
  printf("\nmatrix with values\n");
  print_matrix(n);

  printf("\ntesting matrix_mult with identity matrix\n");
  matrix_mult(m,n);
  print_matrix(n);

  printf("\ntesting matrix_mult with not identity matrix\n");
  m->m[0][2]=14;
  m->m[1][0]=8;
  m->m[2][2]=17;
  print_matrix(m);
  printf("\nmultipled by\n");
  print_matrix(n);
  matrix_mult(m,n);
  printf("\nresult\n");
  print_matrix(n);
  
  return 0;
  }*/

/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

print the matrix
*/
void print_matrix(struct matrix *m) {
  int r=0;
  int c=0;
  while (r<m->rows) {

    //printf("%06.2lf|",(m->m)[r][c]);
    //c++;
    while (c<m->lastcol) {
      printf("\t%06.2lf|",(m->m)[r][c]);

      c++;
    }
    printf("\n");
    r++;
    c=0;

  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns: 

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int r=0;
  int c=0;
  while (r<m->rows) {

    while (c<m->cols) {
      if (r==c)
	m->m[r][c]=1;
      else
	m->m[r][c]=0;
      c++;
    }
    c=0;
    r++;

  }
  m->lastcol=m->cols;
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  int row_a=0;
  int row_b=0;
  int col_b=0;
  int temp=0;

  struct matrix * storage=new_matrix(b->rows,b->cols);
  
  while (row_a<a->rows) {

    while (col_b<b->cols) {
      while (row_b<b->rows) {
	temp+=a->m[row_a][row_b]*b->m[row_b][col_b];
	row_b++;
      }
      //set stuff in storage
      storage->m[row_a][col_b]=temp;
      col_b++;
      row_b=0;
      temp=0;
    }
    col_b=0;
    
    row_a++;
  }
  copy_matrix(storage,b);
  free_matrix(storage);
  
}



/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols 
Returns: 

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)... 
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m 
Returns: 

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
}
