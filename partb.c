#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("USAGE: partb FILEIN FILEOUT\n");
        return 1;
    }

    char *input_file  = argv[1];
    char *output_file = argv[2];

    int fd_in = open(input_file, O_RDONLY);
    if (fd_in < 0) {
        printf("ERROR: %s not found\n", input_file);
        return 1;
    }

    int fd_out = open(output_file,
                      O_WRONLY | O_CREAT | O_TRUNC,
                      0644);
    if (fd_out < 0) {
        close(fd_in);
        printf("ERROR: could not create %s\n", output_file);
        return 1;
    }

    char buf[1024];
    ssize_t bytes_read;

    while ((bytes_read = read(fd_in, buf, sizeof(buf))) > 0) {
        for (ssize_t i = 0; i < bytes_read; i++) {
            if (buf[i] >= 'a' && buf[i] <= 'z') {
                buf[i] -= 32;
            }
        }
        write(fd_out, buf, bytes_read);
    }

    close(fd_in);
    close(fd_out);

    return 0;
}