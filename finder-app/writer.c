#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Missing arguments! Usage: %s <writefile> <writestr>\n", argv[0]);
        return EXIT_FAILURE;
    }
    openlog("write_file", LOG_PID | LOG_PERROR, LOG_USER);

    char *writefile = argv[1];
    char *writestr = argv[2];

    FILE *file = fopen(writefile, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Could not write to file: [%s]", writefile);
        return EXIT_FAILURE;
    }

    fprintf(file, "%s\n", writestr);

    syslog(LOG_DEBUG, "Writing '%s' to %s", writestr, writefile);
    fclose(file);
    closelog();
    return 0;
}
