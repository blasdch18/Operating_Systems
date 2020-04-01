#include <stdio.h>
#include "factorial.h"
#include "answer.h"

int main(int argc, char* argv[]) 
{
	setFnumber(3);
	printf("5! + 1 = %d\n", factorial(5));
	printf("And the answer is: %d\n", answer());
	return 0;
} 
