#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(2, "Usage: strace <on/off/run/dump> [command]\n");
        exit();
    }

    if (strcmp(argv[1], "on") == 0) {
        strace(1);  // Enable tracing
    } else if (strcmp(argv[1], "off") == 0) {
        strace(0);  // Disable tracing
    } else if (strcmp(argv[1], "run") == 0) {
        if (argc < 3) {
            printf(2, "Usage: strace run <command> [args...]\n");
            exit();
        }

        int pid = fork();
        if (pid < 0) {
            printf(2, "Error: Failed to fork process\n");
            exit();
        } else if (pid == 0) {
            strace(1);  // Enable tracing in child
            exec(argv[2], &argv[2]);
            printf(2, "exec: fail\n");
            strace(0);  // Disable tracing
            exit();
        } else {
            wait();  // Wait for child
        }
    } else if (strcmp(argv[1], "dump") == 0) {
        dump();  // Call the dump system call
    } else {
        printf(2, "Invalid argument. Use 'on', 'off', 'run', or 'dump'.\n");
    }

    exit();
}