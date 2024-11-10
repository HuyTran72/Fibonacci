#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables
int *fib_sequence;
int n;

// Thread function to generate Fibonacci sequence
void *generate_fibonacci(void *arg)
{
    fib_sequence[0] = 0;
    if (n > 1)
        fib_sequence[1] = 1;

    for (int i = 2; i < n; i++)
    {
        fib_sequence[i] = fib_sequence[i - 1] + fib_sequence[i - 2];
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <number of Fibonacci numbers>\n", argv[0]);
        return -1;
    }

    // Read the number of Fibonacci numbers from command line
    n = atoi(argv[1]);
    if (n <= 0)
    {
        printf("The number of Fibonacci numbers must be positive.\n");
        return -1;
    }

    // Allocate memory for Fibonacci sequence array
    fib_sequence = (int *)malloc(n * sizeof(int));

    // Create thread
    pthread_t thread;
    pthread_create(&thread, NULL, generate_fibonacci, NULL);

    // Wait for thread to finish
    pthread_join(thread, NULL);

    // Output the Fibonacci sequence
    printf("Fibonacci sequence:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", fib_sequence[i]);
    }
    printf("\n");

    // Free allocated memory
    free(fib_sequence);

    return 0;
}
