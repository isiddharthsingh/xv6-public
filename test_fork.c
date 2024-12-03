#include "types.h"
#include "user.h"

int main() {
    int i;

    // Print the parent process PID
    printf(1, "Parent PID: %d\n", getpid());

    // Spawn multiple child processes
    for (i = 0; i < 3; i++) {
        int pid = fork();

        if (pid == 0) {  // Child process
            // Print the child PID and perform a task
            printf(1, "Child PID: %d is writing...\n", getpid());
            write(1, "Hello from child\n", 17);  // Write a message
            exit();  // Terminate the child process
        } else if (pid > 0) {
            continue;  // Parent process continues to the next iteration
        } else {
            printf(1, "Fork failed\n");  // Handle fork failure
        }
    }

    // Parent process waits for all child processes to complete
    for (i = 0; i < 3; i++) {
        wait();
    }

    // Print a message indicating the parent process is done
    printf(1, "Parent process done.\n");
    exit();  // Terminate the parent process
}