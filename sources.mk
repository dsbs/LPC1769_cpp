###########################################################################
# Dawid Bazan <dawidbazan@gmail.com>
# This file contains source file names and paths 
# This file should be included in Makefile
###########################################################################


###########################################################################
# All subdirectories where source code exists must be defined here
###########################################################################
SUBDIRS = $(sort \
	app \
	lib/CMSIS/Core )
	
###########################################################################
# Sources be build
###########################################################################
# List C++ source fies
CSRCS =  $(sort \
	core_cm3.c \
	system_LPC17xx.c \
	startup_LPC17xx.c )

# List C source files here which must be compiled in ARM-Mode (no -mthumb)
CSRCARM = 

# List C++ source files.
CPPSRC = $(sort \
	main.cpp )

# List C++ source files here which must be compiled in ARM-Mode (no -mthumb)
CPPSRCARM = 

# List Assembler source files
ASRC = 

# List Assembler source files here which must be assembled in ARM-Mode (no -mthumb)
ASRCARM  =

SRCS_ALL = $(CSRC) $(SRCARM) $(CPPSRC) $(CPPSRCARM) $(ASRC) $(ASRCARM)
	
###########################################################################
# Linker script
###########################################################################
LINKERSCRIPT = LPC17xx.ld
