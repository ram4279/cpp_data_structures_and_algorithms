#include <stdio.h>
#include <unistd.h>

int main()
{
	static char mbuf[102400];
	pid_t process_id, parent_process_id;
	process_id = getpid();
	parent_process_id = getppid();
	printf("My process id = %d\n", process_id);
	printf("My parent's process id = %d\n", parent_process_id);

	return 0;
}
