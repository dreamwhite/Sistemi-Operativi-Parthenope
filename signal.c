/*
    This program was written for an assignment about process management and inter-process communication using signals in Linux (well it works even on macOS but who cares).

    The idea is to fork two child processes (A and B). Depending on whether a positive integer passed as a command-line argument is even or odd, 
    the parent sends different signals:

    - If the number is even:
        * The parent sends SIGUSR1 to child A, which computes the cube of the number.
        * Child B just prints a goodbye message and exits.

    - If the number is odd:
        * The parent sends SIGUSR2 to child B, which calculates the reciprocal of the number,
          waits for (2 × number) seconds, and then sends SIGUSR1 to child A.
        * Child A, in this case, waits for SIGUSR1 from B, prints a message, and exits.

    The assignment aims to to explore forks, signals, and basic inter-process synchronization.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t child_a_pid = 0;
pid_t child_b_pid = 0;
int argument = 0;

// Handler for child A: when receiving SIGUSR1 (even case)
void handle_sigusr1_a(int sig) {
    printf("[Child A] Received SIGUSR1.\n");
    int cube = argument * argument * argument;
    printf("[Child A] The cube of %d is %d.\n", argument, cube);
    exit(EXIT_SUCCESS);
}

// Handler for child A when SIGUSR1 is received from B (odd case)
void handle_sigusr1_from_b(int sig) {
    printf("[Child A] Received SIGUSR1 from Child B. Exiting gracefully.\n");
    exit(EXIT_SUCCESS);
}

// Handler for child B: when receiving SIGUSR2 (odd case)
void handle_sigusr2_b(int sig) {
    printf("[Child B] Received SIGUSR2.\n");
    double reciprocal = 1.0 / argument;
    printf("[Child B] The reciprocal of %d is %f.\n", argument, reciprocal);

    int sleep_time = argument * 2;
    printf("[Child B] Sleeping for %d seconds...\n", sleep_time);
    sleep(sleep_time);

    printf("[Child B] Sending SIGUSR1 to Child A...\n");
    kill(child_a_pid, SIGUSR1);

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive_integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    argument = atoi(argv[1]);
    if (argument <= 0) {
        fprintf(stderr, "The argument must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    // Fork first child: A
    child_a_pid = fork();
    if (child_a_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child_a_pid == 0) {
        // Child A process
        if (argument % 2 == 0) {
            signal(SIGUSR1, handle_sigusr1_a);  // Even case
        } else {
            signal(SIGUSR1, handle_sigusr1_from_b);  // Odd case
        }
        pause(); // Wait for signal
        return EXIT_SUCCESS;
    }

    // Fork second child: B
    child_b_pid = fork();
    if (child_b_pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (child_b_pid == 0) {
        // Child B process
        if (argument % 2 == 0) {
            printf("[Child B] Goodbye! (Even case)\n");
            exit(EXIT_SUCCESS);
        } else {
            signal(SIGUSR2, handle_sigusr2_b);  // Odd case
            pause(); // Wait for signal from parent
            return EXIT_SUCCESS;
        }
    }

    // Parent process
    sleep(1); // Small delay to ensure children are ready

    if (argument % 2 == 0) {
        kill(child_a_pid, SIGUSR1);  // Send signal directly to A
    } else {
        kill(child_b_pid, SIGUSR2);  // Start logic via B
    }

    // Wait for both children to finish
    wait(NULL);
    wait(NULL);

    printf("[Parent] Both children have terminated. Exiting.\n");
    return EXIT_SUCCESS;
}
