###########################################################################
# Dawid Bazan <dawidbazan@gmail.com>
# Dariusz Synowiec <devemouse@gmail.com>
# 
# sources.mk
###########################################################################


###########################################################################
# All subdirectories where source code exists must be defined here
###########################################################################
SUBDIRS = $(sort \
			 src/app \
			 src/lib/CMSIS/Core \
			 src/lib/lamp \
			 )

###########################################################################
# Sources to be build
###########################################################################
# List C++ source fies. File suffix must be *.c with case sensitive
CSRCS =  $(sort \
			core_cm3.c \
			system_LPC17xx.c \
			startup_LPC17xx.c \
			)

# List C source files here which must be compiled in ARM-Mode (no -mthumb)
# File suffix must be *.c with case sensitive
CSRCSARM = $(sort \
			  )

# List C++ source files. File suffix must be *.cpp with case sensitive
CPPSRCS = $(sort \
			 main.cpp \
			 lamp.cpp \
			 )

# List C++ source files here which must be compiled in ARM-Mode (no -mthumb)
# File suffix must be *.cpp with case sensitive
CPPSRCSARM = $(sort \
				 )

# List Assembler source files
# File suffix must be *.s with case sensitive
ASRCS = $(sort \
		  )

# List Assembler source files here which must be assembled in ARM-Mode (no -mthumb)
# File suffix must be *.s with case sensitive
ASRCSARM  = $(sort \
				)
###########################################################################
# Linker script
###########################################################################
LINKERSCRIPT = LPC1769.ld

