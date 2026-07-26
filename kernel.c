#include "console.h"
#include "gdt.h"
void kernel_main(void) {
    console_initialize();
    console_print("Hello World From ANURAG'S Kernel\n");
    gdt_initialize();
    console_print("GDT working.\n");
    for (;;);
}
