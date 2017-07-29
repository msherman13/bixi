# teensy3.6
BOARD_TAG 	 = teensy36
MONITOR_PORT = /dev/ttyACM0

ifeq ($(shell uname), Darwin)
PLATFORM=mac
else
PLATFORM=linux
endif

ifeq ($(GEOM), dome)
CXXFLAGS += -DGEOM_DOME
$(info GEOM = dome)
else ifeq ($(GEOM), legs_neck)
CXXFLAGS += -DGEOM_LEGS_NECK
$(info GEOM = legs_neck)
else ifeq ($(GEOM), head)
CXXFLAGS += -DGEOM_HEAD
$(info GEOM = head)
else ifeq ($(GEOM), grid)
CXXFLAGS += -DGEOM_GRID
$(info GEOM = grid)
else
$(error GEOM must be defines as dome, legs_neck, or grid)
endif

ifeq ($(TECHNOLOGY), teensy)
MAKE_PATH = teensy.mk
$(info TECHNOLOGY = teensy)
else
MAKE_PATH = sim.mk
$(info TECHNOLOGY = sim)
endif

include ${MAKE_PATH}
