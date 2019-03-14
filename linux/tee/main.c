#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    int fd;
    int len, slen;

    do {
        /*
         * tee stdin to stdout.
         */
        len = tee(STDIN_FILENO, STDOUT_FILENO,
                  INT_MAX, SPLICE_F_MOVE);

        if (len < 0) {
            perror("tee");
            exit(EXIT_FAILURE);
        } else
            if (len == 0)
                break;

        /*
         * Consume stdin by splicing it to a file.
         */
        while (len > 0) {
            slen = splice(STDIN_FILENO,  NULL, 
                          STDERR_FILENO, NULL,
                          len, SPLICE_F_MOVE);
            if (slen < 0) {
                perror("splice");
                break;
            }
            len -= slen;
        }
    } while (1);

    close(fd);
    exit(EXIT_SUCCESS);
}

