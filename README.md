# Flase 

Welcome to ***Flase***, yes its spelled correctly. The library name is an ode to how I used to misspell false ... and still do sometimes. 
This is meant to be a super simple macro library for writing and running tests in C.

## Usage

It's really simple, all you have to do is `#include "flase.h"` and define your test cases.
There are really only three macro functions you'll need `FLASE_DEFINE_TEST`, `FLASE_ASSERT` and `FLASE_RUN_TEST`. These define tests, add asserts to the tests scope and run the specified test respectively.
Below is a simple example and the output.

```C
// sample.c
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
```

Building `sample.c` and running it we get the following output: (with nice color printing which I unfortunately can't show here)

```diff
FLASE Run Test: simple
	Failed: Whoopsie, sample.c:5
FLASE Report: simple | FAIL [1/2]
FLASE Run Test: apples
FLASE Report: apples | PASS [2/2]
```

## Without stdc
If you really don't want to use the standard library you'll need to provide an alternate definition for the print function that FLASE uses.
You can do this by defining `FLASE_PRINT` to be the name of a function that satisfies the interface of printf.

This is the interface: `int printf(const char* restrict format, ...);`

I would suggest externing your `custom_printf` function from whatever C file you implement it in before you include the FLASE header. After the extern add `#define FLASE_PRINT custom_printf` to tell FLASE what print function to use, the include the FLASE header.

## How I would set this up
I would create one header for each regular header file from your program. Each test header can then test all of the functions / machinary that is laid out in that program header. So for example if you had a `math.h` file I would create a `tests_math.h` test file. I would then include the FLASE header, `math.h` along with whatever other headers you might need. 
After that, I would define all your test functions, and potentially a function to call `FLASE_RUN_TEST` for all of the tests you defined for the header file you are testing. 

In your test application entry point file, I would include all of your test headers including `test_math.h`. You can then call your tests individually using `FLASE_RUN_TEST` or call the function you've created that runs all the tests from each header. 

If you don't want to use stdc, I would define `FLASE_PRINT` before including any of your test headers in the entry point file.

If you are using a tool like cmake, I would recommend building a separate test target.
