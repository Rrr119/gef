#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define VISUAL_PTR_COUNT 32

void *visual_ptrs[VISUAL_PTR_COUNT];

void visual_acceptance_marker(void) {}

static void visual_alloc(int first, int count, size_t size)
{
    for (int i = 0; i < count; i++) {
        visual_ptrs[first + i] = malloc(size);
        memset(visual_ptrs[first + i], 'V', size > 16 ? 16 : size);
    }
}

static void visual_free(int first, int count)
{
    for (int i = 0; i < count; i++) {
        free(visual_ptrs[first + i]);
    }
}

int main(int argc, char **argv)
{
    int layout = argc > 1 ? atoi(argv[1]) : 0;

    if (layout == 0) {
        visual_alloc(0, 4, 0x18);
        visual_alloc(8, 2, 0x38);
    } else if (layout == 1) {
        visual_alloc(0, 3, 0x18);
        visual_free(0, 3);

        visual_alloc(8, 2, 0x38);
        visual_free(8, 2);

        visual_alloc(16, 1, 0x78);
        visual_free(16, 1);
    } else {
        visual_alloc(0, 9, 0x18);
        visual_free(0, 9);

        visual_alloc(16, 3, 0x38);
        visual_free(16, 3);
    }

    visual_acceptance_marker();
    DebugBreak();
    return 0;
}
