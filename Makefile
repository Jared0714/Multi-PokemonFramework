.SUFFIXES:

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR   ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

CTRPFLIB ?= $(CURDIR)/Library

PLGNAME  := Multi-PokemonFramework
PLGINFO  := Multi-PokemonFramework.plgInfo

BUILD    := Build

INCLUDES := Includes\
            Includes/Helpers \
            Includes/Folders \
            Library/Includes \

SOURCES  := Sources \
            Sources/Helpers \
            Sources/Folders

#---------------------------------------------------------------------------------
# Options for code generation
#---------------------------------------------------------------------------------

ARCH      := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS    := $(ARCH) -Os -mword-relocations \
             -fomit-frame-pointer -ffunction-sections -fno-strict-aliasing

CFLAGS    += $(INCLUDE) -D__3DS__

CXXFLAGS  := $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

ASFLAGS   := $(ARCH)
LDFLAGS   := -T $(TOPDIR)/3gx.ld $(ARCH) -Os -Wl,--gc-sections,--strip-discarded,--strip-debug

LIBS      := -lctrpf -lctru
LIBDIRS   := $(CURDIR) $(CTRPFLIB) $(CTRULIB) $(PORTLIBS)

#---------------------------------------------------------------------------------
# No real need to edit anything past this point unless you need to add additional rules for different file extensions
#---------------------------------------------------------------------------------

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT   := $(CURDIR)/$(PLGNAME)
export TOPDIR   := $(CURDIR)
export VPATH    := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \ $(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR  := $(CURDIR)/$(BUILD)

CFILES          := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES        := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES          := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))

export LD       := $(CXX)
export OFILES   := $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE  := $(foreach dir,$(INCLUDES),-I $(CURDIR)/$(dir) ) \
                   $(foreach dir,$(LIBDIRS),-I $(dir)/include) \
                   -I $(CURDIR)/$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L $(dir)/lib)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------

all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------

clean:
	@echo Cleaning ...
	@rm -fr $(BUILD) $(OUTPUT).3gx

re: clean all

#---------------------------------------------------------------------------------

else

DEPENDS := $(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# Main targets
#---------------------------------------------------------------------------------

$(OUTPUT).3gx: $(OUTPUT).elf
$(OUTPUT).elf: $(OFILES)

#---------------------------------------------------------------------------------
# You need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------

%.bin.o: %.bin
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------

%.3gx: %.elf
	@echo Creating $(notdir $@)

ifeq ($(OS),Windows_NT)
	@$(TOPDIR)/3gxtool.exe -s -d $(word 1, $^) $(TOPDIR)/$(PLGINFO) $@
endif

ifeq ($(shell uname),Darwin)
	@WINEDEBUG=-all wine64 $(TOPDIR)/3gxtool64.exe -s -d $(word 1, $^) $(TOPDIR)/$(PLGINFO) $@
endif

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif