#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

const char *errstr[] = {
    "present",
    "write",
    "user",
    "reserved-write",
    "instruction-fetch",
    "protection-key violation",
    "shadow-stack access",
};

bool
is_hexdigit(const char *input)
{
    if (input[0] == '0' && input[1] == 'x') {
        return true;
    }

    return false;
}

void
dump(uint32_t errno)
{
    for (size_t i = 0; i < 7; ++i) {
        printf("%s [%c]\n", errstr[i],
              (errno & (1 << i)) != 0 ? 'x' : ' ');
    }

    if ((errno & (1 << 15)) != 0) {
        printf("SGX violation [x]\n");
    }

    printf("\n");
}

int
main(int argc, char **argv)
{
    uint32_t errno;

    for (size_t i = 1; i < argc; ++i) {
        if (!is_hexdigit(argv[i])) {
            errno = atoi(argv[i]);
            dump(errno);
        } else {
            /*
             * Input would be a string of 0xXXXXXXXX,
             * adding 2 to the pointer removes the
             * '0x' prefix so it can be parsed.
             */
            errno = strtol(argv[i] + 2, NULL, 16);
            dump(errno);
        }
    }

    return 0;
}
