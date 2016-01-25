//
// dtob.cpp
//
// given a command line argument
// C-string representing a numerical value
// in decimal, write to stdout
// the binary representation of that value.
//
// author: Christopher Sprague
//
///////////////////////////////////////////

#include <iostream>
#include <stdlib.h>

//
// power function
// given an integer base and integer exponent,
// return the value of (base)^(exponent)
// note that 0^0 is defined here as 1.
//
int power(int base, int exponent) {
	if (base == 0 && exponent == 0) {
		return 1; // definition here (redundant but w/e)
	}
	if (exponent == 0) {
		return 1;
	}
	if (exponent == 1) {
		return base;
	}
	int sum = base;
	for (int i = 1 ; i < exponent; i++) {
		sum = sum * base;
	}
	return sum;
}

//
// given an integer value_remaining (think remainder)
// return the highest POWER to which 2 can be raised
// that does not EXCEED the value of value_remaining.
//
// in other words, this function is used determine
// where each '1' in the binary representation falls.
//
// if the 2^power = value_remaining, then this is the
// last '1' we need in the binary representation.
//
int p2(int value_remaining) {
	if (value_remaining == 0) {
		return 0; // base case
	}
	int pow = 0;
	for (int i = 0; power(2, i) < value_remaining; i++) {
		pow++;
	}
	if (power(2, pow) > value_remaining) {
		return (pow - 1);
	}
	return pow;
}

static int test_p2_helper(int expected, int actual) {
    int test_pass = (expected == actual);
    if (!test_pass) {
        fprintf(stderr, "Error found in p2 function!\n");
        fprintf(stderr, "Expecting: (%d), got: %d\n", expected, actual);
    }
    return test_pass;
}

static int test_p2() {
    int status = 0;

    printf("Testing \"p2\" function...\n");

    if (test_p2_helper(3, p2(10)) || status)
        status = 1;
    if (test_p2_helper(4, p2(16)) || status)
        status = 1;
    if (test_p2_helper(4, p2(31)) || status)
        status = 1;
    if (test_p2_helper(5, p2(32)) || status)
        status = 1;
    if (test_p2_helper(5, p2(33)) || status)
        status = 1;

	return status;
}

static int print_usage() {
    fprintf(stderr, "Usage: d2b [int-in-decimal]\n");
    return 0;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
        print_usage();
		return EXIT_FAILURE;
	}
	int num;
	if (*(argv[1]) == '0') {
		printf("0\n");
		return EXIT_SUCCESS;
	}
	num = atoi(argv[1]);
	if (!num) {
        fprintf(stderr, "atoi failed to parse input as a valid int (your input was: \"%s\")\n", argv[1]);
        print_usage();
		return EXIT_FAILURE;
	}
	
	test_p2();
	
	int size = p2(num) + 1;
	int bin[size];
	for (int i = 0; i < size; i++) {
		bin[i] = 0 ; // set default to 0, put in 1's later
	}
	int R = num - power(2, p2(num)); // R = value remaining
	bin[p2(num)] = 1;
	while (R != 0) {
		int nhp = p2(R); // next highest power
		bin[nhp] = 1;
		R = R - power(2, p2(R));
	}

	// print out the array backwards
	for (int i = (size - 1); i >= 0; i--) {
		printf("%d", bin[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}





