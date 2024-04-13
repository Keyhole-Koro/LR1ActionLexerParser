#include "utils.h"

char *readUntil(bool (*condition)(char*), char *ipt) {
    size_t buffer_size = 8;

    char *buffer = (char *)malloc(sizeof(char) * buffer_size);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    *buffer = '\0';

    size_t buffer_length = 0;

    while (*ipt && !condition(ipt)) {
        if (buffer_length >= buffer_size - 1) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
            
            if (buffer == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
        }

        strncat(buffer, ipt, 1);
        ipt++;
    }

    buffer[strlen(buffer)] = '\0';

    return buffer;
}
