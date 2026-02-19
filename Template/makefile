# VEXcode makefile 2019_03_26_01

# show compiler output
VERBOSE = 0

# include toolchain options
include vex/mkenv.mk

# location of the project source cpp and c files
SRC_C  = $(wildcard src/*.cpp) 
SRC_C += $(wildcard src/*.c)
SRC_C += $(wildcard src/*/*.cpp) 
SRC_C += $(wildcard src/*/*.c)
SRC_C += $(wildcard lvgl/src/*/*.c) 

OBJ = $(addprefix $(BUILD)/, $(addsuffix .o, $(basename $(SRC_C))) )

# location of include files that c and cpp files depend on
SRC_H  = $(wildcard include/*.h)
SRC_H += ./lv_conf.h

# additional dependancies
SRC_A  = makefile

# project header file locations
INC_F  = include . lvgl lvgl/src

# headers needed to use library
LV_SRC_H += $(wildcard lvgl/lvgl.h) 
LV_SRC_H += $(wildcard lvgl/src/*.h) 
LV_SRC_H += $(wildcard lvgl/src/*/*.h)

LV_DST_H = $(addprefix $(BUILD)/include/, $(LV_SRC_H) )
LV_DST_H += $(BUILD)/include/lv_conf.h $(BUILD)/include/v5lvgl.h

$(BUILD)/include/%: %
	$(Q)$(MKDIR)
	$(Q) $(call copyfile,$^, $@)

vpath %.h lvgl/ include/

# override default library name
PROJECTLIB = libv5lvgl

# build targets
all: $(BUILD)/$(PROJECT).bin

# copy lvgl header files
.PHONY: inc
inc: $(LV_DST_H)
	$(ECHO) "Copy headers to build folder"

# Tell linker where to find libv5lvgl.a
LNK_FLAGS += -L"$(CURDIR)/build"

# include build rules
include vex/mkrules.mk
