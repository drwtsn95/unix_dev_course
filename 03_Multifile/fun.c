#include <stdio.h>
#include "outlib.h"
void output(char *str) {
    printf("%d: %s\012", Count++, str);
}

void usage(char *prog) {
    fprintf(stderr, "v%.2f: Print all arguments\012\t"\
                "Usage: arg1 [arg2 […]]\012", VERSION);
}
