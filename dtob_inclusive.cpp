//
// dtob_inclusive.cpp
//
// given a command line argument
// C-string representing a numerical value
// in decimal, write to stdout
// the binary representation of that value.
//
// extends functionality, this program is designed to
// be able to convert dates via bash's date command
//
// author: Christopher Sprague
//
///////////////////////////////////////////

#include <iostream>
#include <string.h>

//
// power function
// given an integer base and integer exponent,
// return the value of (base)^(exponent)
// note that 0^0 is defined here as 1.
//
int power ( int base, int exponent ) {
	if ( base == 0 && exponent == 0 ) {
		return 1; // definition here (redundant but w/e)
	}
	if ( exponent == 0 ) {
		return 1;
	}
	if ( exponent == 1 ) {
		return base;
	}
	int pow = 1;
	int sum = base;
	for ( int i = 1 ; i < exponent ; i++ ) {
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
int p2 ( int value_remaining ) {
	if ( value_remaining == 0 ) {
		return 0; // base case
	}
	int pow = 0;
	for ( int i = 0 ; power(2,i) < value_remaining ; i++ ) {
		pow++;
	}
	if ( power(2,pow) > value_remaining ) {
		return ( pow - 1 ) ;
	}
	return pow;
}

//
// test function to ensure p2 function
// is working as intended.
//
// format is -
// {(pre-determined correct value)} {function result}
//
void test_p2 ( ) {
	printf("(3) %d\n", p2(10));
	printf("(4) %d\n", p2(16));
	printf("(4) %d\n", p2(31));
	printf("(5) %d\n", p2(32));
	printf("(5) %d\n", p2(33));
	return;
}

//
// main program function.
// reads in args from calling via command line
// 	Usage: d2b {int}
//
int main ( int argc, char* argv[] ) {
	if ( argc == 7 ) { // date format
	// note, format is as follows read in from $date -
	// Fri Feb 28 23:13:57 EST 2014
	// not converting the year, too big a number
		// printf("detected date format\n");
		for ( int i = 1; i<7; i++ ) {
			if (i==3) { // day of month
				int num = atoi(argv[i]);
				int size = p2(num)+1;
				int bin[size];
				for ( int i = 0 ; i < size ; i ++ ) {
					bin[i] = 0 ; // set default to 0, put in 1's later
				}
				int R = num - power(2,p2(num)); // R = value remaining
				bin[p2(num)] = 1;
				while ( R != 0 ) {
					int nhp = p2(R); // next highest power
					bin[nhp] = 1;
					R = R - power(2, p2(R));
				}
				// print out the array backwards
				for ( int i = (size-1) ; i >= 0 ; i-- ) {
					printf("%d", bin[i]);
				}
				printf(" ");
			}
			else if (i==4) { // hour:minute:second
				/*
				step 1: split/token string
				*/
				char* hour = (char*)malloc(sizeof(char)*2); // 2 characters
				char* minute = (char*)malloc(sizeof(char)*2); // 2 characters
				char* second = (char*)malloc(sizeof(char)*2); // 2 characters
				hour = strtok(argv[i],":");
				minute = strtok(NULL,":");
				second = strtok(NULL,":");
				char* args[3] = {hour,minute,second};
				for ( int z = 0; z<3; z++ ) {
					int num = atoi(args[z]);
					int size = p2(num)+1;
					int bin[size];
					for ( int i = 0 ; i < size ; i ++ ) {
						bin[i] = 0 ; // set default to 0, put in 1's later
					}
					int R = num - power(2,p2(num)); // R = value remaining
					bin[p2(num)] = 1;
					while ( R != 0 ) {
						int nhp = p2(R); // next highest power
						bin[nhp] = 1;
						R = R - power(2, p2(R));
					}
					// print out the array backwards
					for ( int i = (size-1) ; i >= 0 ; i-- ) {
						printf("%d", bin[i]);
					}
					if(z!=2){ printf(":"); } else { printf(" "); }
				}
			}
			else { 
				printf("%s ", argv[i]);
			}
		}
		printf("\n") ; return EXIT_SUCCESS ;
			
	}
	if ( argc != 2 ) {
		fprintf(stderr, "Usage: d2b {int}\n");
		exit(EXIT_FAILURE);
	}
	int num;
	if ( *(argv[1]) == '0' ) {
		printf("0\n");
		exit(EXIT_SUCCESS);
	}
	num = atoi(argv[1]);
	if (!( num )) {
		fprintf(stderr, "your input was: %s\n", argv[1]);
		fprintf(stderr, "Usage: d2b {int}\n");
		exit(EXIT_FAILURE);
	}
	
	int size = p2(num)+1;
	int bin[size];
	for ( int i = 0 ; i < size ; i ++ ) {
		bin[i] = 0 ; // set default to 0, put in 1's later
	}
	int R = num - power(2,p2(num)); // R = value remaining
	bin[p2(num)] = 1;
	while ( R != 0 ) {
		int nhp = p2(R); // next highest power
		bin[nhp] = 1;
		R = R - power(2, p2(R));
	}

	// print out the array backwards
	for ( int i = (size-1) ; i >= 0 ; i-- ) {
		printf("%d", bin[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}





