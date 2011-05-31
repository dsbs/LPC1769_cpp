###########################################################################
# Makefile header and help message
###########################################################################
help:
	@echo '                                                                                   '
	@echo ' Dawid Bazan <dawidbazan@gmail.com>                                                '
	@echo ' Dariusz Synowiec <devemouse@gmail.com>                                            '
	@echo '                                                                                   '
	@echo ' Last update on May 2011                                                           '
	@echo '                                                                                   '
	@echo ' Supported commands:                                                               '
	@echo '  make all   : Build software                                                      '
	@echo '  make clean : Clean out files generated by make all command                       '
	@echo '  make flash : Flash microcontroller with compiled software  - not implemented yet '
	@echo '  make doc   : Generate Doxygen documentation - not implemented yet                '
	@echo '  make help  : this help message                                                   '
	@echo '                                                                                   '
	@echo ' Files are generated in release folder                                             '

###########################################################################
# Tool chain files 
###########################################################################
TCHAIN_PREFIX = arm-none-eabi-
CC      = $(TCHAIN_PREFIX)gcc
CPP     = $(TCHAIN_PREFIX)g++
LD      = $(TCHAIN_PREFIX)ld
AR      = $(TCHAIN_PREFIX)ar
OBJCOPY = $(TCHAIN_PREFIX)objcopy
OBJDUMP = $(TCHAIN_PREFIX)objdump
SIZE    = $(TCHAIN_PREFIX)size
NM      = $(TCHAIN_PREFIX)nm
OOCD    = openocd

###########################################################################
# Output path definitions
###########################################################################
# Target file name
TARGET = lpc1769

# Directory for output files (lst, obj, dep, elf, sym, map, hex, bin etc.)
OUTDIR  = release
OBJDIR  = $(OUTDIR)/obj
DEPDIR  = $(OUTDIR)/dep
LSTDIR  = $(OUTDIR)/lst
LOGDIR  = $(OUTDIR)/log
LOGFILE = $(LOGDIR)/$(TARGET).log

# Display or pipe the output of a command and copy it into a log file
TEE     = tee -a $(LOGFILE)

###########################################################################
# included makefiles, input path definitions
###########################################################################
include src/sources.mk
include src/rules.mk

# Add all subfolders with source codes and includes to the makefile path
VPATH = $(SUBDIRS)

###########################################################################
# Define all object files based on source files to be compiled
###########################################################################
COBJS      = $(addprefix $(OBJDIR)/,$(CSRCS:.c=.o))
CPPOBJS    = $(addprefix $(OBJDIR)/,$(CPPSRCS:.cpp=.o))
ASOBJS     = $(addprefix $(OBJDIR)/,$(ASRCS:.s=.o))

OBJS = $(COBJS) $(CPPOBJS) $(ASOBJS)

###########################################################################
# Targets
###########################################################################
# Default target.
all: createdirs gccversion build size
	@echo '---- $(TARGET) built:' | $(TEE)

# Create output directories.
createdirs:
	-@mkdir $(OUTDIR) 2>/dev/null || echo "" >/dev/null
	-@mkdir $(DEPDIR) 2>/dev/null || echo "" >/dev/null
	-@mkdir $(LSTDIR) 2>/dev/null || echo "" >/dev/null
	-@mkdir $(OBJDIR) 2>/dev/null || echo "" >/dev/null
	-@mkdir $(LOGDIR) 2>/dev/null || echo "" >/dev/null
	-@mkdir $(DOCDIR) 2>/dev/null || echo "" >/dev/null

# Display compiler version information.
gccversion: createdirs
	@$(CC) --version
	@$(CC) --version > $(LOGFILE)

# Build all outputs
build: elf hex bin lss sym

# Output files to be build
elf: $(OUTDIR)/$(TARGET).elf
lss: $(OUTDIR)/$(TARGET).lss 
sym: $(OUTDIR)/$(TARGET).sym
hex: $(OUTDIR)/$(TARGET).hex
bin: $(OUTDIR)/$(TARGET).bin

# Calculate sizes of sections. Options:
#  Format Compatibility(A-system default, B-Berkeley's similar)
#  Size data type(d-digital, o-octal, x-hexadecimal)
size: build
	@echo ' '	 | $(TEE)
	@echo '$(SIZE) -A -d --totals $(OUTDIR)/$(TARGET).elf' >> $(LOGFILE)
	@$(SIZE) -A -d --totals $(OUTDIR)/$(TARGET).elf | $(TEE)

# Target: clean project.
clean:
	@echo '---- Cleaning:'
	$(RM) $(OUTDIR)/$(TARGET).map
	$(RM) $(OUTDIR)/$(TARGET).elf
	$(RM) $(OUTDIR)/$(TARGET).hex
	$(RM) $(OUTDIR)/$(TARGET).bin
	$(RM) $(OUTDIR)/$(TARGET).sym
	$(RM) $(OUTDIR)/$(TARGET).lss
	$(RM) $(OBJDIR)/*.o >/dev/null 2>&1
	$(RM) $(LSTDIR)/*.lst >/dev/null 2>&1
	$(RM) $(DEPDIR)/*.d >/dev/null 2>&1
	$(RM) $(LOGDIR)/*.log >/dev/null 2>&1
	@echo ' '
	@echo '---- Cleaned'

# TBD: flash
# use following dependencies after implementing this target
#flash: $(OUTDIR)/$(TARGET).elf
flash:
	$(OOCD) $(OOCD_CL)

doc: createdirs
	@doxygen doxyfile 2>&1
	@cat release/log/doxygen.log

###########################################################################
# Build release files
###########################################################################
# Create final output file (.hex) from ELF output file.
# --output-target ihex  # Write the output file using the ihex object format
$(OUTDIR)/%.hex: $(OUTDIR)/%.elf
	@echo '  OBJCOPY  $(+F) > $(@F)  - hex file' | $(TEE)
	@echo '$(OBJCOPY) -O ihex $< $@' >> $(LOGFILE)
	@$(OBJCOPY) --output-target ihex $< $@ | $(TEE)
	
# Create final output file (.bin) from ELF output file.
# --output-target binary  # Write the output file using the binary object format
$(OUTDIR)/%.bin: $(OUTDIR)/%.elf
	@echo '  OBJCOPY  $(+F) > $(@F)  - binary file' | $(TEE)
	@echo '$(OBJCOPY) -O binary $< $@' >> $(LOGFILE)
	@$(OBJCOPY) -O binary $< $@ | $(TEE)

# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
# -h, --section-headers # Display summary information from the section headers
#                       # of the objfile.
# -S, --source          # Display source code intermixed with disassembly, if
#                       # possible. Implies '-d'.
# -d, --disassemble     # Display the assembler mnemonics for the machine
#                       # instructions from objfile.
# -C, --demangle        # change compiler generated names to readable ones.
# -r, --reloc           # Print the relocation entries of the file.
$(OUTDIR)/%.lss: $(OUTDIR)/%.elf
	@echo '  OBJDUMP  $(+F) > $(@F)  - extended listing/disassembly file' | $(TEE)
	@echo '$(OBJDUMP) -h -S -C -r $< > $@' >> $(LOGFILE)
	@$(OBJDUMP) --section-headers --source --demangle --reloc $< > $@ | $(TEE)

# Create a symbol table from ELF output file.
# -n, --numeric-sort # Sort symbols numerically by their addresses, rather
#                    # than alphabetically by their names
$(OUTDIR)/%.sym: $(OUTDIR)/%.elf
	@echo '  NM       $(+F) > $(@F)  - symbol file' | $(TEE)
	@echo '$(NM) --numeric-sort $< > $@' >> $(LOGFILE)
	@$(NM) -n $< > $@ | $(TEE)

# Link: create ELF output file from object files.
$(OUTDIR)/%.elf: $(OBJS)
	@echo ' ' | $(TEE)
	@echo '  LINK     $(filter %.o,$(+F)) > $(@F)' | $(TEE)
	@echo '$(LD) $(LDFLAGS) $(OBJS) --output $@ ' >> $(LOGFILE)
	@$(LD) $(LDFLAGS) $(OBJS) --output $@ | $(TEE)

###########################################################################
# Compile
###########################################################################
$(OBJDIR)/%.o: %.s
	@echo '  AS  $(<F) > $(@F)' | $(TEE)
	@echo '$(AS) -c $(ASFLAGS) $< -o $@' >> $(LOGFILE)
	@$(AS) -c $(ASFLAGS) $< -o $@; \
	sed -e 's,\($*\)\.o[ :]*,\1.o $(*F).d : ,g' < $(*F).tmp > $(DEPDIR)/$(*F).d; \
	$(RM) -f $(*F).tmp | $(TEE)

$(OBJDIR)/%.o: %.c
	@echo '  CC  $(<F) > $(@F)' | $(TEE)
	@echo '$(CC) -c $(CFLAGS) $< -o $@' >> $(LOGFILE)
	@$(CC) -c $(CFLAGS) $< -o $@; \
	sed -e 's,\($*\)\.o[ :]*,\1.o $(*F).d : ,g' < $(*F).tmp > $(DEPDIR)/$(*F).d; \
	$(RM) -f $(*F).tmp | $(TEE)

$(OBJDIR)/%.o: %.cpp
	@echo '  CPP $(<F) > $(@F)' | $(TEE)
	@echo '$(CPP) -c $(CPPFLAGS) $< -o $@' >> $(LOGFILE)
	@$(CPP) -c $(CPPFLAGS) $< -o $@; \
	sed -e 's,\($*\)\.o[ :]*,\1.o $(*F).d : ,g' < $(*F).tmp > $(DEPDIR)/$(*F).d; \
	$(RM) -f $(*F).tmp | $(TEE)

###########################################################################
# Options for OpenOCD flash-programming
###########################################################################
# Provide path and name for elf file which will be flashed to uC
OOCD_LOADFILE += $(OUTDIR)/$(TARGET).elf

# Specify the JTAG interface which will be used to flash
OOCD_CL += -f interface/oocdlink.cfg

# Specify target uC which will be flashed. 
# TODO: prepare for lpc1769, send to openocd team
# TODO: In the next openocd release this file should be included to /target group, then link directly to openocd/target/lpc1769.cfg
OOCD_CL += -f lpc1769.cfg

# Debug level, 0 = do not output debug messages for openocd
OOCD_CL = -d0




## initialize
#OOCD_CL+=-c init
## enable "fast mode" - can be disabled for tests
#OOCD_CL+=-c "fast enable"
## show the targets
#OOCD_CL+=-c targets
## commands to prepare flash-write
#OOCD_CL+= -c "reset halt"
## increase JTAG frequency a little bit - can be disabled for tests
#OOCD_CL+= -c "jtag_khz 1200"
## flash-write and -verify
#OOCD_CL+=-c "flash write_image erase $(OOCD_LOADFILE)" -c "verify_image $(OOCD_LOADFILE)"
## reset target
#OOCD_CL+=-c "reset run"
## terminate OOCD after programming
#OOCD_CL+=-c shutdown

-include $(DEPDIR)/*

###########################################################################
# Listing of phony targets and default target.
###########################################################################
.PHONY : all help size gccversion build elf hex bin lss sym clean createdirs
.DEFAULT_GOAL := all
# prevent make from deleting *.obj files
.SECONDARY: $(OBJS)
