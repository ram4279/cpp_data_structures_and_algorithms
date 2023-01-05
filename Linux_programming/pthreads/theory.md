1. What happens if we call pthread_create without calling pthread_join ?
- The thread starts executing conncurrently along with the main program flow. Run intro_3_thread_without_pthread_join_call.c for understanding.

In summary, if you do not call pthread_join for a thread that you have created using pthread_create, the thread will continue to execute concurrently with the main program and the main program will not wait for the thread to complete. This can lead to resource leaks if you create and start many threads without waiting for them to complete.
