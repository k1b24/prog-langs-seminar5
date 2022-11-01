#include <stdio.h>

#define print_var(x) printf(#x " is %d", x );
#define some_const 1

int main() {
	int x = 3;
	print_var(some_const);
	printf("\n");
	print_var(x);
	printf("\n");
	print_var(42);
	return 0;
}
