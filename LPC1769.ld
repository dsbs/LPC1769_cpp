/* 
 * Linker script for LCP1769
 *
 * Dawid Bazan <dawidbazan@gmail.com>
 * Dariusz Synowiec <devemouse@gmail.com>
 * 
 * Last update on May 2011
 */


/* 
 * OUTPUT_FORMAT(default, big, little) BFD(Binary File Descriptor) library format 
 * to use for the output file. Describes how many bit machine and what kind of endianess it is
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")

/* MPU - defining regions of memory */
MEMORY
{
  /* On-chip non-volatile memory (ROM): 0x0000 0000 - 0x0007 FFFF */
  rom(rw)   : ORIGIN = 0x00000000, LENGTH = 512K
  
  /* On-chip main SRAM: 0x1000 0000 - 0x1000 7FFF */ 
  ram1(rwx)  : ORIGIN = 0x10000000, LENGTH = 32K
   
  /* 
   * On-chip SRAM AHB SRAM bank 0 and 1(may be reserved for Ethernet and USB): 0x2007 C000 - 0x2008 3FFF 
   * Those are defined separately since physically those are separate momory regions
   */
  ram2(rwx) : ORIGIN = 0x2007C000, LENGTH = 16k
  ram3(rwx) : ORIGIN = 0x20080000, LENGTH = 16k
}

/* Sections memory alignement */
SECTIONS
{
  /* 
   * '.' is location counter which refers to the current location 
   * the location counter is incremented by the size of the output section 
   */

  /* This section holds the text, or executable instructions, of a program */
  . = ORIGIN(rom);

  .stack_address :
  {
     *(*.stack_address .stack_address*)
  } >rom

  .isr_vector :
  {
    KEEP(*(*.isr_vector .isr_vector.*))
  } >rom

  /* ENTRY is by default base address of .text section */
  .text :
  {
    /* CREATE_OBJECT_SYMBOLS - The command tells the linker to create a symbol for each input file */
    CREATE_OBJECT_SYMBOLS
    /* 
     * KEEP the interrupt vector section: When link-time garbage collection is in use ("--gc-sections"), 
     * it is often useful to mark sections that should not be eliminated
     */
    KEEP(*(*.reset_handler .reset_handler.*))
   
    /* ROM sections */
    *(.rom)
    *(.rom.b)
    
    /* 
     * The "*" is a wildcard which matches any file name. The expression "*(.text)" 
     * means all ".text" input sections in all input files
     */
    *(.text .text.*)
    
    /* The linkonce is to support C++ vague linkage(inline functions, vtables for virtual functions etc.) */
    *(.gnu.linkonce.t.*)
    
    /* 
     * Procedure Linkage Table (PLT) generation for multiple load regions containing code when in Base Platform mode 
     * Option is useful when you have multiple load regions that might be moved relative to each other when the image 
     * is dynamically loaded. The linker generates a PLT for each load region so that calls do not have to be 
     * extended to reach a distant PLT
     */
    *(.plt)
    
    /* Warnings section */
    *(.gnu.warning)
		
    /* These sections are provided to store ARM/Thumb interworking code */
    *(.glue_7)
    *(.glue_7t)
    
    /* 
     * This section is needed for some instructions which might be here generated because of 
     * hardware bug for VFP11 coprocessor hardware,
     */
    *(.vfp11_veneer)

    /* TODO: description is needed */
    *(.ARM.extab* .gnu.linkonce.armextab.*)

    /* This section holds Language Specific Data */
    *(.gcc_except_table)
    
    /*
     * eh - exception handling, this section contains a pointer to the .eh_frame section which is accessible 
     * to the runtime support code of a C++ application. 
     * This section may also contain a binary search table which may be used by 
     * the runtime support code to more efficiently access records in the .eh_frame section 
     */
    *(.eh_frame_hdr)
    
    /* eh - exception handling, this section contains information necessary for frame unwinding during exception handling */
    *(.eh_frame)
    
    /* Initialized read-only data */
    *(.rodata .rodata*)
    
    /* The linkonce is to support C++ vague linkage(inline functions, vtables for virtual functions etc.) */
    *(.gnu.linkonce.r.*)
    
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    /* KEEP the init section */
    /* 
     * .init_array contains pointers to blocks of code that need to be executed
     * when an application is being initialized (before main() is called).  Its
     * used for a number of things, but the primary use is in C++ for running
     * static constructors; a secondary use that is sometimes used is to
     * initialize IO systems in the C library 
     */    
    KEEP(*(.init))
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    __preinit_array_start = .;
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    __preinit_array_end = .;
    PROVIDE_HIDDEN (__preinit_array_end = .);
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    __init_array_start = .;
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    __init_array_end = .;
    PROVIDE_HIDDEN (__init_array_end = .);
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    KEEP(*(.fini))
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    __fini_array_start = .;
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    __fini_array_end = .;

    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    /* This section contains a list of global constructor function pointers */ 
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))
		
		/* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    /* This section contains a list of global destructor function pointers */
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))

    /* Provide to the code the end of ROM address */
    _etext = .;
    PROVIDE(etext = .);
    
    /* Provide to the code ROM address of the start of fast code */
    _sifastcode = .;
    PROVIDE(sifastcode = .);
  } >rom

  /* The exception-handling index tables for ARM uC */ 
  __exidx_start = .;
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } >rom
  __exidx_end = .;
  
  /* fastcode - copied at startup and executed in RAM */ 
  .fastcode :
  {
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN (4);
    /* Provide to the code the start address of fastcode section */
    _sfastcode = . ;
    PROVIDE(sfastcode = .);
    
    /* These sections are provided to store ARM/Thumb interworking code */
    *(.glue_7t) 
    *(.glue_7)
    
    /* Fast code */
    *(.fastcode)
    
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN (4);
    /* Provide to the code the end address of fastcode section */
    _efastcode = . ;
    PROVIDE(efastcode = .);
    /* 
     * >ram1 AT>rom - the VMA(Virtual Memory Address) is in ram1, the LMA(Load Memory Address) is in rom
     * This feature is designed to make it easy to build a ROM image 
     */
  } >ram1 AT>rom

  /* These section hold initialized data that contribute to the program's memory image */
  . = ORIGIN(ram1);
  .data :
  {
    /* Provide to the code start of address for the initialization values */
    _sidata = .;
    PROVIDE(sidata = .);
    *(.sidata)

    /* Provide to the code start of address for ram data */
    _sdata = .;
    PROVIDE(sdata = .);    
    
    /* Set the location counter to the next 4 aligned boundary */
    . = ALIGN(4);
    /* 
     * This section contains information necessary for registering compiled Java classes
     * The contents are compiler-specific and used by compiler initialization functions
     */
    KEEP(*(.jcr))
    /* 
     * This section holds the read-only portion of the GLobal Offset Table 
     * This section may be made read-only after relocations have been applied 
     */
    *(.got.plt) *(.got)
    
    /* Data memory */
    *(.shdata)
    
    /* 
     * vtable is a static pointer which is created as a part of the compilation 
     * and it gets filled whenever constructor is called 
     */
    *(vtable vtable.*)
    
    /* Data memory */
    *(.data .data.*)
    
    /* The linkonce is to support C++ vague linkage(inline functions, vtables for virtual functions etc.) */
    *(.gnu.linkonce.d*)
    
    /* RAM data */
    *(.ram)

    /* Provide to the code the end of RAM1 address */
    _edata = .;
    PROVIDE(edata = .);
    /* 
     * >ram1 AT>rom - the VMA(Virtual Memory Address) is in ram1, the LMA(Load Memory Address) is in rom
     * This feature is designed to make it easy to build a ROM image 
     */    
  } >ram1 AT>rom
  
  /* 
   * This section holds data that contributes to the program's memory image. 
   * The program may treat this data as uninitialized. 
   * However, the system shall initialize this data with zeroes when the program begins to run 
   * The section occupies no file space
   */
  /* 
   * The section should be marked as not loadable, so that it will not be loaded into
   * memory when the program is run
   */
  .bss (NOLOAD) :
  {
    /* Provide to the code the start of RAM address where italized data is stored */
    _sbss = .;
    PROVIDE(sbss = .);
    
    /* Statically-allocated variables represented solely by zero-valued bits initially */
    *(.shbss)
          
    /* Statically-allocated variables represented solely by zero-valued bits initially */
    *(.bss .bss.*)
    
    /* The linkonce is to support C++ vague linkage(inline functions, vtables for virtual functions etc.) */
    *(.gnu.linkonce.b*)
    
    /* A special notation is needed for common symbols,  because in many object file formats
     * common symbols do not have a particular input section. The linker treats common symbols 
     * as though they are in an input section named "COMMON" 
     */
    *(COMMON)
    
    /* RAM data */
    *(.ram.b)
    
    /* Provide to the code the end of RAM address where italized data is stored */
    _ebss = .;
    PROVIDE(ebss = .);
    _end = .;
  } >ram1
   
   
  /* Start of heap section */
  .heap (NOLOAD) :
  {
    *(.heap)
  } >ram1
   


  
  _estack = ORIGIN(ram1) + LENGTH(ram1) - 16;
  /*PROVIDE(estack = ORIGIN(ram1) + LENGTH(ram1) - 16);*/

  /* These section hold initialized data that contribute to the program's memory image */
  . = ORIGIN(ram2);
  .ram2 :
  {
    /* Provide to the code start of address for RAM2 */
    _sdatar2 = .;
    PROVIDE(sdatar2 = .);     
    
    /* RAM2 data */
    *(.ram2)
          
    /* Provide to the code end of address for RAM2 */
    _edatar2 = .;
    PROVIDE(edatar2 = .);           
  } >ram2
   
  /* These section hold initialized data that contribute to the program's memory image */
  . = ORIGIN(ram3);
  .ram3 :
  {
     /* Provide to the code start of address for RAM3 */
     _sdatar3 = .;
     PROVIDE(sdatar3 = .);     
     
     /* RAM3 data */
     *(.ram3)
           
     /* Provide to the code end of address for RAM3 */
     _edatar3 = .;
     PROVIDE(edatar3 = .);    
  } >ram3
   
  /* Stabs refers to a format for information that describes a program to a debugger */
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
