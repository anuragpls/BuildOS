#include "idt.h"
#include "console.h"
void isr_handler(struct registers* regs)
{
  switch (regs->int_no) {
    case 0:
        console_print("Divide by zero\n");
        break;
    case 1:
        console_print("Debug\n");
        break;
    case 2:
        console_print("Non maskable interrupt\n");
        break;
    case 3:
        console_print("Breakpoint\n");
        break;
    case 4:
        console_print("Overflow\n");
        break;
    case 5:
        console_print("Bound range exceeded\n");
        break;
    case 6:
        console_print("Invalid opcode\n");
        break;
    case 7:
        console_print("Device not available\n");
        break;
    case 8:
        console_print("Double fault\n");
        break;
    case 9:
        console_print("Coprocessor segment overrun\n");
        break;
    case 10:
        console_print("Invalid TSS\n");
        break;
    case 11:
        console_print("Segment not present\n");
        break;
    case 12:
        console_print("Stack-segment fault\n");
        break;
    case 13:
        console_print("General protection fault\n");
        break;
    case 14:
        console_print("Page fault\n");
        break;
    case 15:
        console_print("Reserved exception\n");
        break;
    case 16:
        console_print("x87 floating-point exception\n");
        break;
    case 17:
        console_print("Alignment check\n");
        break;
    case 18:
        console_print("Machine check\n");
        break;
    case 19:
        console_print("SIMD floating-point exception\n");
        break;
    case 20:
        console_print("Virtualization exception\n");
        break;
    case 21:
        console_print("Control protection exception\n");
        break;
    default:
        console_print("Unknown/reserved exception\n");
        break;
}
  for(;;);
}