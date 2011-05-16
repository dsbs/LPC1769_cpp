/* Linker script for LCP1769
 * Dawid Bazan <dawidbazan@gmail.com>
 */

OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
SEARCH_DIR(.)
GROUP(-lgcc -lc -lcs3 -lcs3unhosted -lcs3micro)


/* ENTRY(_SystemInit) */

/* MPU - defining regions of memory */
MEMORY
{
   /* On-chip non-volatile memory: 0x0000 0000 - 0x0007 FFFF */
   ROM(rw)   : ORIGIN = 0x00000000, LENGTH = 512K
   
   /* On-chip SRAM: 0x1000 0000 - 0x1000 7FFF */ 
   RAM(rwx)  : ORIGIN = 0x10000000, LENGTH =  32K
   
   /* On-chip SRAM AHB SRAM bank 0 and 1(Reserved for Ethernet and USB): 0x2007 C000 - 0x2008 3FFF */
   RAM2(rwx) : ORIGIN = 0x2007C000, LENGTH = 32k
}


SECTIONS
{
   /* 
    * '.' so called 'dot' is location counter which refers to the current location 
    * the location counter is incremented by the size of the output section 
    */
   /* .ROM  start is needed instead magic number can it be done? The same with other sections TBD */
   . = 0x00000000;
   /* Output section name */
   .text :
   {
      CREATE_OBJECT_SYMBOLS
      *(.isr_vector)
      /*
       * '*' so called 'asterisk' is wildcard which matches any file name 
       * The expression '*(.text)' means all '.text' input sections in all input files
       */
      /* Input section name which will be placed into this output section - program code */
      *(.text)
      /* Store at 'etext' the address of the end of this section */
      _etext = .;
      /* Provide to the code etext value */
      PROVIDE(etext = .);
   } >ROM
  
   /* RAM start address */
   . = 0x10000000;
   .data :
   {
      /* Store at 'sidata' the address of the beginning of this section */
      _sidata = .;
      /* Provide to the code sidata value */
      PROVIDE(sidata = .);  
      /* Store at 'sdata' the address of the beginning of this section */
      _sdata = .;
      /* Provide to the code sdata value */
      PROVIDE(sdata = .);      
      /* Data memory */
      *(.data)    
      /* Store at 'edata' the address of the end of this section */
      _edata = .;
      /* Provide to the code edata value */
      PROVIDE(edata = .);         
   } >RAM
  
   /* Statically-allocated variables represented solely by zero-valued bits initially */
   .bss :
   {
      /* Store at 'sbss' the address of the beginning of this section */
      _sbss = .;
      /* Provide to the code sbss value */
      PROVIDE(sbss = .);   
      /* Statically-allocated variables represented solely by zero-valued bits initially */
      *(.bss)
      /* Store at 'bss' the address of the end of this section */
      _ebss = .;
      /* Provide to the code ebss value */
      PROVIDE(ebss = .);   
   } >RAM
   
   /* Start of heap section */
   .heap :
   {
      *(.heap)
   } >RAM
   
   /* TBD: get define from code */
   /* Top of stack section */
   .stack (0x10008000) :
   {
      _estack = .;
      PROVIDE(estack = .);
      *(.stack)
   } >RAM
   
   /* RAM2 start address */
   . = 0x2007C000;
   .RAM2 :
   {
      *(.RAM2)
   } >RAM2
       
}
