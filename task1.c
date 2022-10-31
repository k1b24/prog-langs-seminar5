#include <stdio.h>

#define print_var(x) printf(#x " is %d", x );

int main() {
	const int c = 1;
	int x = 3;
	print_var(c);
	printf("\n");
	print_var(x);
	printf("\n");
	print_var(42);
	return 0;
}
