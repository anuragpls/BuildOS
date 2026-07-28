#include "console.h"
#include "gdt.h"
#include "idt.h"
void kernel_main(void) {
    console_initialize();
    console_print("Hello World From ANURAG'S Kernel\n");
    gdt_initialize();
    console_print("GDT working.\n");
    idt_initialize();
    console_print("IDT working.\n");
    volatile int numerator = 1;
    volatile int zero = 0;
    volatile int x = numerator / zero;
    for (;;);
}
