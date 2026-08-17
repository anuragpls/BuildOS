#include "idt.h"
#define IDT_ENTRIES 256
static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr ip;
extern void idt_flush(uint32_t idt_ptr_address);
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

static void* isr_stub_table[] = {
    (void*)isr0,  (void*)isr1,  (void*)isr2,  (void*)isr3,
    (void*)isr4,  (void*)isr5,  (void*)isr6,  (void*)isr7,
    (void*)isr8,  (void*)isr9,  (void*)isr10, (void*)isr11,
    (void*)isr12, (void*)isr13, (void*)isr14, (void*)isr15,
    (void*)isr16, (void*)isr17, (void*)isr18, (void*)isr19,
    (void*)isr20, (void*)isr21, (void*)isr22, (void*)isr23,
    (void*)isr24, (void*)isr25, (void*)isr26, (void*)isr27,
    (void*)isr28, (void*)isr29, (void*)isr30, (void*)isr31
};
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
  for (int i = 0; i < 32; i++) {
    idt_set_entry(i, (uint32_t)isr_stub_table[i], 0x08, 0, 0x8E);
}
  idt_flush((uint32_t)&ip);
}