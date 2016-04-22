#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s field str\n", argv[0]);
        return 1;
    }

    char field [strlen(argv[1]) + 2];
    memcpy(field, argv[1], strlen(argv[1]));
    strcat(field, "=");
    const size_t field_len = strlen(field);
    char* shift_line = NULL;
    size_t length = 0;
    char* next_field = NULL;
    char prev_char;
    char* line;

    while(getline(&line, &length, stdin) != -1) {
        shift_line = strstr(line, field);

        if(shift_line != NULL) {
            shift_line += field_len;
            next_field = strstr(shift_line, "\t");

            if(next_field == NULL) {
                next_field = strstr(shift_line, " ");
            }

            if(next_field != NULL) {
                prev_char = next_field[0];
                next_field[0] = '\0';
            }

            if(strstr(shift_line, argv[2]) != NULL) {
                if(next_field != NULL) {
                    next_field[0] = prev_char;
                }

                printf("%s\n", line);
            }
        }

        free(line);
        length =  0;
    }

    return 0;
}
