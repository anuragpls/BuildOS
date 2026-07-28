#include "idt.h"
#include "console.h"
void isr_handler(struct registers* regs)
{
  if(regs->int_no==0)
  {
    console_print("Trying to divide by zero error \n");
  }
  for(;;);
}