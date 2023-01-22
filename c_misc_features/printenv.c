#include <stdio.h>

int main(int argc, char** argv, char** env)
{
	char** e_ptr = env;
	printf("e_ptr = %s\n", *e_ptr);
	while (*env) {
		printf("%s\n", *env);
		env++;
	}
	return 0;
}
