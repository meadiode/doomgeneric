

BINARY_NAME ?= doomrl

PLATFORM ?= PLATFORM_DESKTOP
TARGET_PLATFORM = PLATFORM_DESKTOP_GLFW

RAYLIB_RELEASE_PATH  ?= $(RAYLIB_PATH)/src
RAYLIB_LIB_PATH ?= /usr/local/lib


SOURCE = dummy.c                 \
		 am_map.c                \
		 doomdef.c               \
		 doomstat.c              \
		 dstrings.c              \
		 d_event.c               \
		 d_items.c               \
		 d_iwad.c                \
		 d_loop.c                \
		 d_main.c                \
		 d_mode.c                \
		 d_net.c                 \
		 f_finale.c              \
		 f_wipe.c                \
		 g_game.c                \
		 hu_lib.c                \
		 hu_stuff.c              \
		 info.c                  \
		 i_cdmus.c               \
		 i_endoom.c              \
		 i_joystick.c            \
		 i_scale.c               \
		 i_sound.c               \
		 i_system.c              \
		 i_timer.c               \
		 memio.c                 \
		 m_argv.c                \
		 m_bbox.c                \
		 m_cheat.c               \
		 m_config.c              \
		 m_controls.c            \
		 m_fixed.c               \
		 m_menu.c                \
		 m_misc.c                \
		 m_random.c              \
		 p_ceilng.c              \
		 p_doors.c               \
		 p_enemy.c               \
		 p_floor.c               \
		 p_inter.c               \
		 p_lights.c              \
		 p_map.c                 \
		 p_maputl.c              \
		 p_mobj.c                \
		 p_plats.c               \
		 p_pspr.c                \
		 p_saveg.c               \
		 p_setup.c               \
		 p_sight.c               \
		 p_spec.c                \
		 p_switch.c              \
		 p_telept.c              \
		 p_tick.c                \
		 p_user.c                \
		 r_bsp.c                 \
		 r_data.c                \
		 r_draw.c                \
		 r_main.c                \
		 r_plane.c               \
		 r_segs.c                \
		 r_sky.c                 \
		 r_things.c              \
		 sha1.c                  \
		 sounds.c                \
		 statdump.c              \
		 st_lib.c                \
		 st_stuff.c              \
		 s_sound.c               \
		 tables.c                \
		 v_video.c               \
		 wi_stuff.c              \
		 w_checksum.c            \
		 w_file.c                \
		 w_main.c 			     \
		 w_wad.c 			     \
		 z_zone.c 			     \
		 w_file_stdc.c 		     \
		 i_input.c 			     \
		 i_video.c               \
		 doomgeneric.c           \
		 vfs.c 					 \
		 $(BUILD_DIR)/vfs_data.c \
		 doomgeneric_raylib.c


ROOT_DIR=$(shell pwd)
BUILD_DIR=$(ROOT_DIR)/build

CROSS_COMPILE ?= 

RM     ?= rm
ECHO   ?= @echo
CP     ?= cp
MKDIR  ?= mkdir
SED    ?= sed
PYTHON ?= python3

AS      = $(CROSS_COMPILE)as
AR      = $(CROSS_COMPILE)ar
GCC     = $(CROSS_COMPILE)gcc
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE    = $(CROSS_COMPILE)size
STRIP   = $(CROSS_COMPILE)strip

CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result
CFLAGS += -g -D_DEBUG

INCLUDE_PATHS = -I. -I./build -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external

LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt 
LDLIBS += -lX11

LDFLAGS = -L. -L$(RAYLIB_RELEASE_PATH) -L$(RAYLIB_PATH)/src
LDFLAGS += -L$(RAYLIB_LIB_PATH)

OBJ = 
OBJ += $(addprefix $(BUILD_DIR)/, $(SOURCE:.c=.o))
OBJ_DIRS = $(sort $(dir $(OBJ)))

all: $(ROOT_DIR)/$(BINARY_NAME)

vpath %.c . $(TOP)
$(BUILD_DIR)/%.o: %.c
	$(ECHO) "CC $<"
	$(CC) $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM) -D$(TARGET_PLATFORM) -c -o $@ $<

$(OBJ): | $(OBJ_DIRS)
$(OBJ_DIRS):
	mkdir -p $@

$(BUILD_DIR)/vfs_data.c $(BUILD_DIR)/vfs_data.h:
	$(ECHO) "Generating virtual FS data..."
	$(PYTHON) makefsdata.py ./wads -o $(BUILD_DIR)/vfs_data

$(ROOT_DIR)/$(BINARY_NAME): $(OBJ)
	$(ECHO) "LINK $@"
	$(GCC) -o $@ $(OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)
	$(SIZE) $@

print-cfg:
	$(ECHO) "OBJ              = $(OBJ)"
	$(ECHO) "BUILD_DIR        = $(BUILD_DIR)"
	$(ECHO) "INCLUDE_PATHS    = $(INCLUDE_PATHS)"
	$(ECHO) "CFLAGS           = $(CFLAGS)"
	$(ECHO) "DEFINES          = $(DEFINES)"

clean:
	$(RM) -rf $(BUILD_DIR)
	$(RM) -f $(ROOT_DIR)/$(BINARY_NAME)

.PHONY: all clean print-cfg
