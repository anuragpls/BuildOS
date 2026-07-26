#include "gdt.h"
#define GDT_ENTRIES 3
static struct gdt_entry gdt[GDT_ENTRIES];
static struct gdt_ptr gp;
extern void gdt_flush(uint32_t gdt_ptr_address);
static void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
  gdt[index].base_low = (base & 0xFFFF);
  gdt[index].base_middle = (base >> 16) & 0xFF;
  gdt[index].base_high = (base >> 24) & 0xFF;
  gdt[index].limit_low = (limit & 0xFFFF);
  gdt[index].granularity = (limit >> 16) & 0x0F;
  gdt[index].granularity |= (gran & 0xF0);
  gdt[index].access = access;
}
void gdt_initialize(void)
{
    gp.limit=(sizeof(struct gdt_entry)*GDT_ENTRIES)-1;
    gp.base=(uint32_t)&gdt;
    gdt_set_entry(0,0,0,0,0); //null descriptor
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // code seg descriptor 0x9A bits
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // data seg descriptor 0x92 bits
    gdt_flush((uint32_t)&gp);
}
