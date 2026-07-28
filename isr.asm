global isr0
extern isr_handler
 isr0 :
  push 0 ;
  push 0 ;
  pusha ;
  push esp ;
  call isr_handler
  add esp, 4
  popa
  add esp, 8
  iret

