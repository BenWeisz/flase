#include <stdio.h>

int banana_f(const char* restrict format, ...)
{
	printf("I like bananas\n");
}

#define FLASE_PRINT banana_f
#include "flase.h"

FLASE_DEFINE_TEST( simple )
{
	FLASE_ASSERT( 1 == 0, "Whoopsie" );
	FLASE_ASSERT( 1 == 1, "This must be true" );
}

FLASE_DEFINE_TEST( apples )
{
	FLASE_ASSERT( 1 < 2, "Correcto" );
	FLASE_ASSERT( 2 > 1, "Yes" );
}

int main()
{
	FLASE_RUN_TEST( simple );
	FLASE_RUN_TEST( apples );

	return 0;
} 
