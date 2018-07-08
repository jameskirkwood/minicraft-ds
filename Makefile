#------------------------------------------------------------------------------
# Minicraft DS Makefile
#------------------------------------------------------------------------------
$(if $(CUSTARD),,$(error "🍮\
  Cannot locate Custard (https://github.com/jameskirkwood/ds-custard). Please\
  set CUSTARD to the path to your working copy, either in your environment, or\
  in a command line argument to make. (eg. $$make CUSTARD=path/to/custard)"))
#------------------------------------------------------------------------------
GAME_TITLE      := Minicraft DS
GAME_SUBTITLE1  := A game by Markus Persson
GAME_SUBTITLE2  := NDS port by James Kirkwood
GAME_ICON       := assets/icon.bmp
VERSION         := Minicraft DS (prerelease) 0.1
#------------------------------------------------------------------------------

TARGET    := MinicraftDS
SOURCES   := source assets
BUILD     := build

INCLUDE   := $(foreach dir,$(SOURCES),-I$(dir)) -I$(BUILD)
CXXFLAGS  := -std=c++17 -Wall -O3 -DVERSION='"$(VERSION)"'
LIBDIRS   := $(CUSTARD)
LIBS      := -lcustard

include $(CUSTARD)/custard.mk

#------------------------------------------------------------------------------
# files
#------------------------------------------------------------------------------

CPPFILES  := $(shell find $(SOURCES) -name '*.cpp')
SFILES    := $(shell find $(SOURCES) -name '*.s')
PNGFILES  := $(shell find $(SOURCES) -name '*.png')
WAVFILES  := $(shell find $(SOURCES) -name '*.wav')

HOUTPUTS  := $(PNGFILES:%.png=$(BUILD)/%.h)
HOUTPUTS  += $(WAVFILES:%.wav=$(BUILD)/%_wav.h)

SFILES    += $(PNGFILES:%.png=$(BUILD)/%.s)

OFILES    := $(WAVFILES:%=$(BUILD)/%.o)
OFILES    += $(CPPFILES:%.cpp=$(BUILD)/%.o)
OFILES    += $(SFILES:%.s=$(BUILD)/%.o)

#------------------------------------------------------------------------------
# targets
#------------------------------------------------------------------------------

$(TARGET).nds: $(TARGET).elf $(GAME_ICON)
$(TARGET).elf: $(HOUTPUTS) $(OFILES)

_DS_MENU.DAT: $(TARGET).nds
	r4denc $< $<.dat
	mv $<.dat _DS_MENU.DAT

.PHONY: run clean

run: $(TARGET).nds
	open $(TARGET).nds

clean:
	rm -fr $(BUILD) $(TARGET).{elf,nds,map} _DS_MENU.DAT

#------------------------------------------------------------------------------
# dependencies
#------------------------------------------------------------------------------
-include  $(OFILES:.o=.d)
#------------------------------------------------------------------------------
