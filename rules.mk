###########################################################################
# Compiler settings
###########################################################################
# C/C++ compiler flags
# -mcpu=cortex-m3                  # CPU name
# -mthumb-interwork                # Compile with using mixed instructions ARM and Thumb
# -gdwarf-2                        # Debugging format
# -O2                              # Optimalization level
# -fpromote-loop-indices           # Convert loop indices to word-sized quantities
# -Wall -Wextra                    # Turn all optional warnings plus extra optional
#                                  # optional warnings from -Wall and -Wextra below above line
# -MD -MP -MF $(OUTDEPDIR)/$(@F).d # Compiler flags to generate dependency files
#                                  # -Wa -pass to the assembler, -adhlns -create assembler listing
# $(patsubst %,-I%,$(SUBDIRS)) -I. # Seach thru all subdirs

CFLAGS =  \
	-mcpu=cortex-m3 \
	-gdwarf-2 \
	-O2 \
	-fpromote-loop-indices \
	-Wnested-externs \
	-std=gnu99 \
	-Wall -Wextra \
	-Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wshadow -Wcast-qual -Wcast-align \
	-fno-rtti -fno-exceptions \
	-MD -MP -MF $(OUTDEPDIR)/$(@F).d \
	-Wa,-adhlns=$(addprefix $(OUTLSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<)))) \
	$(patsubst %,-I%,$(SUBDIRS)) -I.

#CFLAGS_SUB = cflags.sub
#CFLAGS =  @$(CFLAGS_SUB)
#$(CFLAGS_SUB):
	#@echo -mcpu=cortex-m3 >>$@
	#@echo -mthumb >>$@
	#@echo -mthumb-interwork >>$@
	#@echo -gdwarf-2 >>$@
	#@echo -O2 >>$@
	#@echo -fpromote-loop-indices >>$@
	#@echo -Wall -Wextra >>$@
	#@echo -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -Wshadow -Wcast-qual -Wcast-align >>$@
	#@echo -MD -MP -MF $(OUTDEPDIR)/$(@F).d >>$@
	#@echo -Wa,-adhlns=$(addprefix $(OUTLSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<)))) >>$@
	#@echo $(patsubst %,-I%,$(SUBDIRS)) -I.>>$@

# C only compiler flags
#   -Wnested-externs      				# Warn if an extern declaration is encountered within a function
#   -std=gnu99							# Defined standard: c99 plus GCC extensions
#   $(patsubst %,-I%,$(SUBDIRS)) -I.    # Seach thru all subdirs

CONLYFLAGS = 

# C++ only compiler flags
#   -fno-rtti -fno-exceptions           # If you will not use virtual functions 
#                                       # those setting flags will optimalize the code
#   $(patsubst %,-I%,$(SUBDIRS)) -I.    # Seach thru all subdirs
CPPFLAGS = 

# Assembler compliler flags
# -mcpu=cortex-m3 \                # CPU name
# -mthumb-interwork \              # Compile with using mixed instructions ARM and Thumb
# -Wa, -gdwarf-2 \                 # Debugging format
# -x assembler-with-cpp \          # Source files C++ for assembler
# -D__ASSEMBLY__ \                 # Allows include files in assemler
#                                  # -Wa -pass to the assembler, -adhlns -create assembler listing
# $(patsubst %,-I%,$(SUBDIRS)) -I. # Seach thru all subdirs
ASFLAGS  = \
	-mcpu=cortex-m3 \
	-Wa, -gdwarf-2 \
	-x assembler-with-cpp \
	-D__ASSEMBLY__ \
	-Wa,-adhlns=$(addprefix $(OUTLSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<)))) \
	$(patsubst %,-I%,$(SUBDIRS)) -I.

# Linker flags
# -lc -lm -lgc -lstdc++                                             # Link to standard libraries (lLibrary)
# -T$(LINKERSCRIPT)                                                 # Use this linker script
# -nostartfiles                                                     # Do not use the standard system startup files when linking
# -Wl # pass to the linker, -Map -create map file,
# --cref -Output # a cross reference table,
# --gc-sections -Enable garbage collection of unused input sections
LDFLAGS = \
	-lc -lm -lgcc -lstdc++ \
	-Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref,--gc-sections \
	-T$(LINKERSCRIPT) -nostartfiles
