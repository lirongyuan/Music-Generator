#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "bits.h"

void test1()
{
	unsigned int a = 9;

	unsigned int b = 3;

	printf("a:\n");
	printBits(a);
	
	printf("b:\n");
	printBits(b);
	
	printf("a&b:\n");
	printBits(a&b);
	
	printf("a|b:\n");
	printBits(a|b);
	
	printf("a^b:\n");
	printBits(a^b);

	printf("~a:\n");
	printBits(~a);
}

void test2()
{
	unsigned int a = 9;

	printf("a:\n");
	printBits(a);
	
	setBitAt(&a, 10, 1);

	printf("a after setBitAt(&a,10,1):\n");

	printBits(a);
	setBitAt(&a, 20, 1);

	printf("a after setBitAt(&a,20,1):\n");
	printBits(a);
	
	
	setBitAt(&a, 0, 0);
	printf("a after setBitAt(&a,0,0):\n");
	printBits(a);
	
	setBitAt(&a, 3, 0);
	printf("a after setBitAt(&a,3,0):\n");
	printBits(a);
	
	
}

void test3()
{
	unsigned int a = 0xFFFF1009;

	printf("a:\n");
	printBits(a);

	int v = getBitAt(a, 3);
	printf("getBitAt(3)=%d\n", v);


	v = getBitAt(a, 10);
	printf("getBitAt(10)=%d\n", v);


	v = getBitAt(a, 20);
	printf("getBitAt(20)=%d\n", v);

	v = getBitAt(a, 5);
	printf("getBitAt(5)=%d\n", v);
}

void test4()
{
	unsigned int a = 0x6F245FF2;
	unsigned int b = 0x7F67FF89;

	printf("a:\n");
	printBits(a);
	printf("countBits(a,1)=%d\n", countBits(a,1));
	printf("countBits(a,0)=%d\n", countBits(a,0));

	printf("b:\n");
	printBits(b);
	printf("countBits(b,1)=%d\n", countBits(b,1));
	printf("countBits(b,0)=%d\n", countBits(b,0));
}

void test5()
{
	unsigned int a = 0x6FE45F92;
	unsigned int b = 0x7F67FF89;
	int pos, count;

	printf("a:\n");
	printBits(a);
	count = maxContinuousOnes(a, &pos);
	printf("maxContinuousOnes(a, &pos)=%d pos=%d\n", count, pos);

	printf("b:\n");
	printBits(b);
	count = maxContinuousOnes(b, &pos);
	printf("maxContinuousOnes(b, &pos)=%d pos=%d\n", count, pos);
}

int main( int argc, char ** argv )
{
	if (argc < 2) {
		printf("test_bits [test1|test2|test3|test4|test5]\n");
		exit(1);
	}

	if (strcmp(argv[1],"test1")==0) {
		test1();
	}
	else if (strcmp(argv[1],"test2")==0) {
		test2();
	}
	else if (strcmp(argv[1],"test3")==0) {
		test3();
	}
	else if (strcmp(argv[1],"test4")==0) {
		test4();
	}
	else if (strcmp(argv[1],"test5")==0) {
		test5();
	}
	else {
		printf("Invalid test\n");
		return 1;
	}
	return 0;
}

