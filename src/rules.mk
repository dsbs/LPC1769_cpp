###########################################################################
# Dawid Bazan <dawidbazan@gmail.com>
# Dariusz Synowiec <devemouse@gmail.com>
#
# rules.mk
###########################################################################

###########################################################################
# Automatically generated files containing rules
###########################################################################
#CFLAGS_SUB = $(OUTDIR)/sub/cflags.sub
#CONLYFLAGS_SUB = $(OUTDIR)/sub/conlyflags.sub
#CPPFLAGS_SUB = $(OUTDIR)/sub/cppflags.sub
#ASFLAGS_SUB = $(OUTDIR)/sub/asflags.sub

###########################################################################
# Compiler settings
###########################################################################
# THUMB rules
# -mthumb           # Generate code for the Thumb instruction set.  The default is to use the 32-bit
#                   # ARM instruction set. This option automatically enables either 16-bit Thumb-
#                   # 1 or mixed 16/32-bit Thumb-2 instructions based on the ‘-mcpu=name’ and
#                   # ‘-march=name’ options. This option is not passed to the assembler. If you want
#                   # to force assembler file st ob einterprete da sThum bcode ,eithe rad d a‘.thumb’
#                   # directive to the source or pass the ‘-mthumb’ option directly to the assembler
#                   # by prefixin gi twit h‘-Wa’.
# -mthumb-interwork # Generate code which supports calling between the ARM and Thumb instruction
#                   # sets. Without this option the two instruction sets cannot be reliably used inside
#                   # one program. The default is ‘-mno-thumb-interwork’, since slightly larger code
#                   # is generated when ‘-mthumb-interwork’ is specified.
THUMB = -mthumb -mthumb-interwork

# listing generation rules
# TODO: describe listing generation parameters
LSTGEN = -Wa,-adhlns=$(LSTDIR)/$(*F).lst 

# dependency generation rules
# TODO: describe dependency generation parameters
DEPGEN = -MD -MP -MF $(*F).tmp

# C/C++ compiler flags
# -mcpu=cortex-m3                  # CPU name
# -mthumb-interwork                # Compile with using mixed instructions ARM and Thumb
# -gdwarf-2                        # Debugging format
# -O2                              # Optimalization level
# -fpromote-loop-indices           # Convert loop indices to word-sized quantities
# -Wall -Wextra                    # Turn all optional warnings plus extra optional
#                                  # optional warnings from -Wall and -Wextra below above line
CFLAGS_SUB = \
				 $(patsubst %,-I%,$(SUBDIRS)) \
				 -I. \
				 -mcpu=cortex-m3 \
				 -gdwarf-2 \
				 -O2 \
				 -fpromote-loop-indices \
				 -Wall \
				 -Wextra \
				 -Wimplicit \
				 -Wcast-align \
				 -Wpointer-arith \
				 -Wredundant-decls \
				 -Wshadow \
				 -Wcast-qual \
				 -Wcast-align \
				 -fno-exceptions

# C only compiler flags
#   -Wnested-externs      				# Warn if an extern declaration is encountered within a function
#   -std=gnu99							# Defined standard: c99 plus GCC extensions
CONLYFLAGS_SUB = \
					  -Wnested-externs \
					  -std=gnu99

# C++ only compiler flags
#   -fno-rtti -fno-exceptions           # If you will not use virtual functions 
#                                       # those setting flags will optimalize the code
CPPFLAGS_SUB = \
					-fno-rtti

# Assembler compliler flags
# -mcpu=cortex-m3 \                # CPU name
# -mthumb-interwork \              # Compile with using mixed instructions ARM and Thumb
# -Wa, -gdwarf-2 \                 # Debugging format
# -x assembler-with-cpp \          # Source files C++ for assembler
# -D__ASSEMBLY__ \                 # Allows include files in assemler
#                                  # -Wa -pass to the assembler, -adhlns -create assembler listing
ASFLAGS_SUB = \
				  $(patsubst %,-I%,$(SUBDIRS)) -I. \
				  -mcpu=cortex-m3 \
				  -Wa, -gdwarf-2 \
				  -x assembler-with-cpp \
				  -D__ASSEMBLY__

# Linker flags
# --warn-common         # Warn when a common symbol is combined with another common
#                       # symbol or with a symbol definition.
# --warn-constructors   # Warn if any global constructors are used.
# --warn-section-align  # Warn if the address of an output section is changed
#                       # because of alignment.
# --warn-shared-textrel # Warn if the linker adds a DT TEXTREL to a shared object.
# --warn-alternate-em   # Warn if an object has alternate ELF machine code.
# -nostartfiles         # Do not use the standard system startup files when linking
# -Wl                   # pass to the linker, -Map -create map file,
# --cref                # Output a cross reference table,
# --gc-sections         # Enable garbage collection of unused input sections
# -T$(LINKERSCRIPT)     # Use this linker script

LDFLAGS = \
			 --warn-common \
			 --warn-constructors \
			 --warn-section-align \
			 --warn-shared-textrel \
			 --warn-alternate-em \
			 -nostartfiles \
			 -Map=$(OUTDIR)/$(TARGET).map --cref --gc-sections  \
			 -T$(LINKERSCRIPT)

