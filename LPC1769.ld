/* 
 * Linker script for LCP1769
 * Dawid Bazan <dawidbazan@gmail.com>
 * May 2011
 */

/* 
 * OUTPUT_FORMAT(default, big, little) BFD(Binary File Descriptor) library format 
 * to use for the output file. Describes how many bit machine and what kind of endianess it is
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
/* The first instruction to execute in a program */
ENTRY(Reset_Handler)
/* TBD: not see Reset_handler */


/* MPU - defining regions of memory */
MEMORY
{
   /* On-chip non-volatile memory (ROM): 0x0000 0000 - 0x0007 FFFF */
   ROM(rw)   : ORIGIN = 0x00000000, LENGTH = 512K
   
   /* On-chip main SRAM: 0x1000 0000 - 0x1000 7FFF */ 
   RAM1(rwx)  : ORIGIN = 0x10000000, LENGTH =  32K
   
   /* On-chip SRAM AHB SRAM bank 0 and 1(You may reserve for Ethernet and USB): 0x2007 C000 - 0x2008 3FFF */
   RAM2(rwx) : ORIGIN = 0x2007C000, LENGTH = 16k
   RAM3(rwx) : ORIGIN = 0x20080000, LENGTH = 16k
}

/* 
 * Most of the sections and subsections are standard sections of ELF(Executable and Linking Format) 
 * file and are described in Linux Standard Base (LSB) 
 * the documentation can be found under following link
 * http://refspecs.freestandards.org
 * 
 * Some of the sections and subsections are defined to be used in the user code(like for e.g. section .stack) 
 */
SECTIONS
{
   /* 
    * '.' so called 'dot' is location counter which refers to the current location 
    * the location counter is incremented by the size of the output section 
    */
   /* .ROM  start is needed instead magic number can it be done? The same with other sections TBD */
   . = 0x00000000;
   /* This section holds the text, or executable instructions, of a program */
   .text :
   {
      /* CREATE_OBJECT_SYMBOLS - The command tells the linker to create a symbol for each input file */
      CREATE_OBJECT_SYMBOLS
        KEEP(*(.isr_vector .isr_vector.*))
        *(.text .text.*)
        *(.gnu.linkonce.t.*)
		*(.gnu.warning)
        *(.glue_7)
        *(.glue_7t)
        /* This section holds Language Specific Data */
        *(.gcc_except_table)
        /* Initialized read-only data */
        *(.rodata .rodata*)
        *(.gnu.linkonce.r.*)
        . = ALIGN(4);
        KEEP(*(.init))
        
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;
        
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;
        
        . = ALIGN(4);
		KEEP(*(.fini))
		
		. = ALIGN(4);
		__fini_array_start = .;
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		__fini_array_end = .;

        /* This section contains a list of global constructor function pointers */ 
		. = ALIGN(0x4);
		KEEP (*crtbegin.o(.ctors))
		KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
		KEEP (*(SORT(.ctors.*)))
		KEEP (*crtend.o(.ctors))
		
        . = ALIGN(4);
        /* This section contains a list of global destructor function pointers */
        KEEP (*crtbegin.o(.dtors))
        KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
        KEEP (*(SORT(.dtors.*)))
        KEEP (*crtend.o(.dtors))
      /*
       * '*' so called 'asterisk' is wildcard which matches any file name 
       * The expression '*(.text)' means all '.text' input sections in all input files
       */
      /* Input section name which will be placed into this output section - program code */
      /**(.text)*/
      /* Store at 'etext' which is the address of the end of this section */
      _etext = .;
   } >ROM

	.eh_frame_hdr : ALIGN (4)
	{
		KEEP (*(.eh_frame_hdr))
	} >ROM
	.eh_frame : ALIGN (4)
	{
		KEEP (*(.eh_frame))
	} >ROM

  
    __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >ROM
  __exidx_end = .;
  
    /**************************************************/
  /* fastcode - copied at startup & executed in RAM */
  
  .fastcode :
  {
    . = ALIGN (4);
    _sfastcode = . ;
  
    *(.glue_7t) *(.glue_7)
    *(.fastcode)
    
    /* add other modules here ... */
  
    . = ALIGN (4);
    _efastcode = . ;
    _sidata = .;
  } >RAM1 AT>ROM
  
   /* These section hold initialized data that contribute to the program's memory image */
   . = 0x10000000;
   .data :
   {
   /*TBD: use this below? instead of address of section above*/
   /*_sidata = LOADADDR (.data);*/
      /* Store at 'sidata' the address of the beginning of this section */
      _sidata = .;

      /* Store at 'sdata' the address of the beginning of this section */
      _sdata = .;

    *(vtable vtable.*)
    *(.data .data.*)
    *(.gnu.linkonce.d*)

    . = ALIGN(4);
     
      /* Data memory */
      /**(.data)*/  
      /* Store at 'edata' the address of the end of this section */
      _edata = .;       
   } >RAM1
  
    /* This section holds data that contributes to the program's memory image. 
     * The program may treat this data as uninitialized. 
     * However, the system shall initialize this data with zeroes when the program begins to run. 
     * The section occupies no file space
     */
     /*TBD: NLOAD use?*/
   .bss (NOLOAD) :
   {
      /* Store at 'sbss' the address of the beginning of this section */
      _sbss = .;
    *(.bss .bss.*)
    *(.gnu.linkonce.b*)
    *(COMMON)
    
      /* Statically-allocated variables represented solely by zero-valued bits initially */
     /* *(.bss)*/
      /* Store at 'bss' the address of the end of this section */
      _ebss = .;
   } >RAM1
   
   /* Start of heap section */
   .heap (NOLOAD):
   {
      *(.heap)
   } >RAM1
   
   /* TBD: get define from code */
   /* Top of stack section */
   .stack (0x10007000) :
   {
      _estack = .;
      PROVIDE(estack = .);
      *(.stack)
   } >RAM1
   
    /******************************************/
  /* For stack section */
/*    .stackarea (NOLOAD) :
    {
      . = ALIGN(8);
      _sstack = .;

    *(.stackarea .stackarea.*)

    . = ALIGN(8);
    _estack = .;

    . = ALIGN(4);
    _end = . ;
    PROVIDE (end = .);

    } > IRAM0
  _stack = ORIGIN(IRAM0) + LENGTH(IRAM0);
 
 */  
    /* These section hold initialized data that contribute to the program's memory image */
   . = 0x2007C000;
   .RAM2 :
   {
      *(.RAM2)
   } >RAM2
   
    /* These section hold initialized data that contribute to the program's memory image */
   . = 0x20080000;
   .RAM3 :
   {
      *(.RAM3)
   } >RAM3   
   

   /* This section contains debugging information. The contents are not specified as part of the LSB -TBD find description*/
   .stab          0 : { *(.stab) }
   /* This section contains strings associated with the debugging infomation contained in the .stab section */
   .stabstr       0 : { *(.stabstr) }
   .stab.excl     0 : { *(.stab.excl) }
   .stab.exclstr  0 : { *(.stab.exclstr) }
   .stab.index    0 : { *(.stab.index) }
   .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
   /* DWARF debug sections.
    * Symbols in the DWARF debugging sections are relative to the beginning
    * of the section so we begin them at 0
    */
    
   /* DWARF 1 */
   /* Debugging tables (may include line number data) */
   .debug          0 : { *(.debug) }
    /* Line number data for debugging */
   .line           0 : { *(.line) }
   /* GNU DWARF 1 extensions */
   .debug_srcinfo  0 : { *(.debug_srcinfo) }
   .debug_sfnames  0 : { *(.debug_sfnames) }
   /* DWARF 1.1 and DWARF 2 */
   .debug_aranges  0 : { *(.debug_aranges) }
   .debug_pubnames 0 : { *(.debug_pubnames) }
   /* DWARF 2 */
   .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
   .debug_abbrev   0 : { *(.debug_abbrev) }
   .debug_line     0 : { *(.debug_line) }
   .debug_frame    0 : { *(.debug_frame) }
   .debug_str      0 : { *(.debug_str) }
   .debug_loc      0 : { *(.debug_loc) }
   .debug_macinfo  0 : { *(.debug_macinfo) }
   /* SGI/MIPS DWARF 2 extensions */
   .debug_weaknames 0 : { *(.debug_weaknames) }
   .debug_funcnames 0 : { *(.debug_funcnames) }
   .debug_typenames 0 : { *(.debug_typenames) }
   .debug_varnames  0 : { *(.debug_varnames) }  
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }

  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) }
}
