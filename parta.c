#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Declare the buffer to use. Do NOT change!
    enum { BUFSIZE = 8 };
    char buffer[BUFSIZE];

    ssize_t n;
    while ((n = read(STDIN_FILENO, buffer, BUFSIZE)) > 0) {
        for (ssize_t i = 0; i < n; i++) {
            if (isalpha((unsigned char)buffer[i])) {
                putchar(buffer[i]);
            }
        }
    }

    return 0;
}