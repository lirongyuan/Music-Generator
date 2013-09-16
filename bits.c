#include <stdio.h>
#include <stdlib.h>
// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	// Add your code here
	int i;
	unsigned int bitmask;
	for(i=31;i>=0&&(bitmask=(1<<i));i--)
		(bitmap&bitmask)?putchar('1'):putchar('0');
	printf("\n10987654321098765432109876543210\n");
}

// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	// Add your code here
	unsigned int bitmask=(1<<i);
	(bitValue)?(*bitmap=((*bitmap)|bitmask)):(*bitmap=((*bitmap)&(~bitmask)));
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	// Add your code here
	unsigned int bitmask=(1<<i);
	return (bitmask&bitmap)?1:0;
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here
	unsigned int bitmask;
	int count0,count1,i;
	for(i=0,count1=0,count0=0;(i<32)&&(bitmask=(1<<i));i++)
		(bitmap&bitmask)?count1++:count0++;
	return (bitValue)?count1:count0;
}

// It returns the number of largest consecutive 1s in "bitmap".
// "*position" is set to the beginning of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	// Add your code here
	int arr[40][2],i,j,in,count,max;
	unsigned int bitmask=1;
	for(i=0,j=0,in=0,count=0,max=0;(i<32)&&(bitmask=(1<<i));i++){
	  if(bitmask&bitmap){
			count++;
	  }else{
		  if(count>0){
		    arr[j][0]=count;
		    arr[j++][1]=i-count;
		  }
		  count=0;
		}	
	}
	for(i=0;i<j;i++)
		if(arr[i][0]>arr[max][0])
			max=i;
	*position=arr[max][1];
	return arr[max][0];
}

