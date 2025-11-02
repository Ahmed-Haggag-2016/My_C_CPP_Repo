#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    free(ptr);   // first free (ok)
    free(ptr);   // ❌ double free
    return 0;
}
