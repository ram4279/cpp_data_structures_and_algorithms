#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int no_of_mails = 0;

void* increment_mail()
{
	// mail received
	// increment mail count
	for (int i = 0; i < 100000; i++)
		no_of_mails++;
	return NULL;
}


int main()
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, increment_mail, NULL);
	pthread_create(&t2, NULL, increment_mail, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("No of mails received = %d\n", no_of_mails);
	return 0;

}

/*
 * Due to race condition the output will not be 200000 as you expected
 * Reasons
 * - Both thread running parallely
 * - Thread 2 paused for sometime and thread 1 continues its execution and vice versa
 * 	 and after this the register of the resumed thread updates the global variable incorrectly
    .L3:                                                                                                                                                                                      
    movl    no_of_mails(%rip), %eax <- eax is the register                                                             
    addl    $1, %eax                                                                                                                                                                     
    movl    %eax, no_of_mails(%rip)                                                                                                                                                           addl    $1, -4(%rbp)
 *
 */



