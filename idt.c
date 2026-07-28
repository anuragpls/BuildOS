#include "idt.h"
#define IDT_ENTRIES 256
static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr ip;
extern void idt_flush(uint32_t idt_ptr_address);
extern void isr0(void);
static void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t zero, uint8_t type_attr)
{
   idt[index].offset_low = (base & 0xFFFF);
   idt[index].offset_high = (base >> 16) & 0xFFFF;
   idt[index].selector = selector;
   idt[index].zero = zero;
   idt[index].type_attr = type_attr;
}
void idt_initialize(void)
{
  ip.limit = (sizeof (struct idt_entry) * IDT_ENTRIES) -1;
  ip.base = (uint32_t)&idt;
  for(int i=0; i<256; i++)
  {
    idt_set_entry(i,0,0,0,0);
  }
  idt_set_entry(0, (uint32_t)isr0, 0x08, 0, 0x8E);
  idt_flush((uint32_t)&ip);
}