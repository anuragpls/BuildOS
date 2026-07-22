#include "console.h"

void kernel_main(void) {
    console_initialize();
    console_print("Hello, kernel!\n");
    for (;;);
}
