#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	// Add your code here
  int i,j,maxIndex,minIndex;//i,j are index
  void *curr, *max, *min, *temp;//curr is the current element. max is the max element. min is min element.
  if(ascending){
		for(i=0;i<n;i++){ 
			minIndex=i;
			for(j=i;j<n;j++){
				curr=(void *)((char *)array+j*elementSize);
				min=(void *)((char *)array+minIndex*elementSize);
				if(compFunc(curr,min)<0){
					minIndex=j;
				}
			}
			temp=malloc(elementSize);
			curr=(void *)((char *)array+i*elementSize);
			min=(void *)((char *)array+minIndex*elementSize);
			memcpy(temp,min,elementSize);
			memcpy(min,curr,elementSize);
			memcpy(curr,temp,elementSize);
		}
  }else{
		for(i=0;i<n;i++){ 
			maxIndex=i;
			for(j=i;j<n;j++){
				curr=(void *)((char *)array+j*elementSize);
				max=(void *)((char *)array+maxIndex*elementSize);
				if(compFunc(curr,max)>0){
					maxIndex=j;
				}
			}
			temp=malloc(elementSize);
			curr=(void *)((char *)array+i*elementSize);
			max=(void *)((char *)array+maxIndex*elementSize);
			memcpy(temp,max,elementSize);
			memcpy(max,curr,elementSize);
			memcpy(curr,temp,elementSize);
		}
  }
  free(temp);
}


