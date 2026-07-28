#ifndef IDT_H
#define IDT_H
#include <stdint.h>
struct idt_entry
{ 
    uint16_t offset_low;   // handler address, bits 0-15
    uint16_t selector;     // which GDT code segment to use
    uint8_t  zero;         // unused, always 0
    uint8_t  type_attr;    // gate type + flags
    uint16_t offset_high;  // handler address, bits 16-31
}__attribute__((packed));
struct idt_ptr
{
    uint16_t limit; //size of idt array
    uint32_t base; //base address of idt array
}__attribute__((packed));
struct registers
{
    uint32_t edi, esi, ebp, esp_dummy, ebx, edx, ecx, eax;  // reversed pusha order
    uint32_t int_no, err_code;                                // isr0's own pushes
    uint32_t eip, cs, eflags;   //CPU auto pushes
}__attribute__((packed));
void idt_initialize (void);
#endif