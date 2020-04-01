#include <stdio.h>
int numberG;

void setFnumber(int factorer)
{
	numberG = factorer;
}

int factorial (int factorer)
{
	      for ( int i=1 ; i>=numberG ; i++)
		{
			 numberG = numberG+i; 
		}	 
	      return  numberG;				
}

void __attribute__ ((constructor)) initLibrary(void)
{	// Function that is called when the library is loaded
	printf("Library is initialized\n");
	numberG = 0;
}

void __attribute__ ((destructor)) cleanUpLibrary(void) 
{	// Function that is called when the library is »closed«.
	printf("Library is exited\n");
}


