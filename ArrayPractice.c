// from 2014

#include <stdio.h>

#define LEN_A 10

void printArray(int[], int); 
void reverse(int[], int);     
double average(int[], int);   
void insert(int[], int, int, int);    
int lessThanAverage(int[], int);    
int secondLargest(int[], int);       
void rotateRight(int[], int, int);   
void arrayCopy(int[], int[], int);   
void initialize(int[], int, int);    

int main(int argc, char **argv)
{
  int A[] = {9, 21, 321, 117, 27, 64, 13, 9, 12, 208};
  int B[LEN_A+1];
  int newValue = 505;

  printf("A[] is:\n");
  printArray(A, LEN_A);

  initialize(B, LEN_A+1, 0);
  printf("B[] is:\n");
  printArray(B, LEN_A+1);

  arrayCopy(B, A, LEN_A);
  printf("but now it's\n");
  printArray(B, LEN_A+1);

  insert(B, newValue, 0, LEN_A);
  printf("and after inserting %d at the beginning it's\n", newValue);
  printArray(B, LEN_A+1);

  printf("The average of A[] is %f\n", average(A,LEN_A));
  printf("There are %d items in A[] less than this.\n", lessThanAverage(A,LEN_A));

  reverse(A, LEN_A);
  printArray(A, LEN_A);

  printf("The second largest item in A[] is %d\n", secondLargest(A, LEN_A));

  rotateRight(A, LEN_A, 3);
  printArray(A, LEN_A);

  return 0;
}

/* prints A[] inside parentheses with each value separated
   by commas to stdout (which will be the screen). */
void printArray(int A[], int length) 
{
 int i;

 printf("[");
 for (i = 0; i < length; i++) {
   if (i > 0) printf(" ,");
   printf("%d", A[i]);
 }
 printf("]\n");
}

/* returns the average of the items in A[] or 0.0 if A is empty */
double average(int A[], int length) 
{
  int i;
  double sum, avg;

  for (i = 0; i < length; i++) {
    sum += A[i];
  }

  avg = (sum / length);
  return avg;
}

/* returns the number of items in A that are less than the
   average of the items in A */
int lessThanAverage(int A[], int length) 
{
  int i;
  int x = 0;
  double avg, sum;

  for (i = 0; i < length; i++) {
    sum += A[i];
  }

  avg = (sum / length);

  for (i = 0; i < length; i++) {
    if (A[i] < avg) x++; 
  }

  return x;
}

/* Reverses the values in A[].  For example, if before the function,
   A[] contained [1,2,3,4,5], after the function, A[] contains
   [5,4,3,2,1] */
void reverse(int A[], int length) 
{
  int temp[length];
  int i;
  
  for (i = 0; i < length; i++) {
    temp[i] = A[i];
  }

  for (i = 0; i < length; i++) {
    A[length - 1 - i] = temp[i];
  }
}

/* returns the second largest item in A[], or -1 if len < 2 */
int secondLargest(int A[], int length) 
{
  int i, first, second;

  if (length < 2) return -1;
  for (i = 0; i < length; i++) {
    if (i == 0) {
      first = A[i];
    } else if (i == 1) {
      if (A[i] > first) {
	second = first;
	first = A[i];
      } else {
	second = A[i];
      }
    } else {
      if (A[i] > first) {
	second = first;
	first = A[i];
      } else if (A[i] > second) {
	second = A[i];
      }
    }
  }
  return second;
}

/* rotates the values in the array numPlaces to the right */
/* for example, if A[] is initially 10,20,30,40,50, and numPlaces=2 */
/* after the function finishes, A[] would be 40,50,10,20,30 */
void rotateRight(int A[], int length, int numPlaces) 
{
  int temp[length];
  int i;

  for (i = 0; i < length; i++) {
    temp[i] = A[i];
  }

  for (i = numPlaces; i < (length + numPlaces); i++) {
    A[i % length] = temp[i - numPlaces];
  }
}

/* inserts the value n in A[] at the given index and shifts
   all other values up one position.  A[] contains length items.

   It is up to the caller to make sure that there is enough space
   in A[] to accommodate the new item, and that the index is valid. */
void insert(int A[], int n, int index, int length) // array b, 505, 0, 10
{
  int i;
  int temp;

  for (i = index; i <= length; i++) {
  temp = A[i];
  A[i] = n;
  n = temp;
  } 
}

/* copies the first numItems from S to D. */
void arrayCopy(int D[], int S[], int numItems) 
{
  int i;

  for (i = 0; i < (numItems); i++)
    {
      D[i] = S[i];
    }
}


/* sets the first len elements of A to initialValue */
void initialize(int A[], int len, int initialValue) 
{
  int i;

  for (i = 0; i < (len - 1); i++)
    {
      A[i] = initialValue;
    }
}
