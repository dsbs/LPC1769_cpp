###########################################################################
# Dawid Bazan <dawidbazan@gmail.com>
# Dariusz Synowiec <devemouse@gmail.com>
#
# rules.mk
###########################################################################

###########################################################################
# Automatically generated files containing rules
###########################################################################
CFLAGS_SUB = $(OUTDIR)/sub/cflags.sub
CONLYFLAGS_SUB = $(OUTDIR)/sub/conlyflags.sub
CPPFLAGS_SUB = $(OUTDIR)/sub/cppflags.sub
ASFLAGS_SUB = $(OUTDIR)/sub/asflags.sub
LDFLAGS_SUB = $(OUTDIR)/sub/ldflags.sub
FLAGS_SUB = $(CFLAGS_SUB) $(CONLYFLAGS_SUB) $(CPPFLAGS_SUB) $(ASFLAGS_SUB) $(LDFLAGS_SUB)

createsubdir:
	-@mkdir $(OUTDIR)/sub 2>/dev/null || echo "" >/dev/null

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
$(CFLAGS_SUB): createsubdir
	@$(RM) $@
	@echo $(patsubst %,-I%,$(SUBDIRS)) >>$@
	@echo -I. >>$@
#	@echo -Wa,-adhlns=$(addprefix $(OUTLSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<)))) >>$@
	@echo -mcpu=cortex-m3 >>$@
	@echo -gdwarf-2 >>$@
	@echo -O2 >>$@
	@echo -fpromote-loop-indices >>$@
	@echo -Wall >>$@
	@echo -Wextra >>$@
	@echo -Wimplicit >>$@
	@echo -Wcast-align >>$@
	@echo -Wpointer-arith >>$@
	@echo -Wredundant-decls >>$@
	@echo -Wshadow >>$@
	@echo -Wcast-qual >>$@
	@echo -Wcast-align >>$@
	@echo -fno-exceptions >>$@
	@echo -MD -MP -MF $(OUTDEPDIR)/$(@F).d >>$@

# C only compiler flags
#   -Wnested-externs      				# Warn if an extern declaration is encountered within a function
#   -std=gnu99							# Defined standard: c99 plus GCC extensions
#   $(patsubst %,-I%,$(SUBDIRS)) -I.    # Seach thru all subdirs
$(CONLYFLAGS_SUB): createsubdir
	@$(RM) $@
	@echo -Wnested-externs >>$@
	@echo -std=gnu99 >>$@

# C++ only compiler flags
#   -fno-rtti -fno-exceptions           # If you will not use virtual functions 
#                                       # those setting flags will optimalize the code
#   $(patsubst %,-I%,$(SUBDIRS)) -I.    # Seach thru all subdirs
$(CPPFLAGS_SUB): createsubdir
	@$(RM) $@
	@echo -fno-rtti >>$@

# Assembler compliler flags
# -mcpu=cortex-m3 \                # CPU name
# -mthumb-interwork \              # Compile with using mixed instructions ARM and Thumb
# -Wa, -gdwarf-2 \                 # Debugging format
# -x assembler-with-cpp \          # Source files C++ for assembler
# -D__ASSEMBLY__ \                 # Allows include files in assemler
#                                  # -Wa -pass to the assembler, -adhlns -create assembler listing
# $(patsubst %,-I%,$(SUBDIRS)) -I. # Seach thru all subdirs
$(ASFLAGS_SUB): createsubdir
	@$(RM) $@
	@echo -mcpu=cortex-m3 >>$@
	@echo -Wa, -gdwarf-2 >>$@
	@echo -x assembler-with-cpp >>$@
	@echo -D__ASSEMBLY__ >>$@
	@echo -Wa,-adhlns=$(addprefix $(OUTLSTDIR)/, $(notdir $(addsuffix .lst, $(basename $<)))) >>$@
	@echo $(patsubst %,-I%,$(SUBDIRS)) -I. >>$@

# Linker flags
# -lc -lm -lgc -lstdc++                                             # Link to standard libraries (lLibrary)
# -T$(LINKERSCRIPT)                                                 # Use this linker script
# -nostartfiles                                                     # Do not use the standard system startup files when linking
# -Wl # pass to the linker, -Map -create map file,
# --cref -Output # a cross reference table,
# --gc-sections -Enable garbage collection of unused input sections
$(LDFLAGS_SUB): 
	@$(RM) $@
	@echo -Map=$(OUTDIR)/$(TARGET).map --cref --gc-sections  >>$@
	@echo -T$(LINKERSCRIPT) -nostartfiles -Iapp -Ilib/CMSIS/Core -I. >>$@
#	@echo -lc -lm -lgcc -lstdc++ \ >>$@

