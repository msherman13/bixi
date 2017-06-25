# teensy3.6
BOARD_TAG 	 = teensy36
MONITOR_PORT = /dev/ttyACM0

ifeq ($(GEOM), dome)
CXXFLAGS += -DGEOM_DOME
$(info GEOM = dome)
else ifeq ($(GEOM), legs_neck)
CXXFLAGS += -DGEOM_LEGS_NECK
$(info GEOM = legs_neck)
else ifeq ($(GEOM), grid)
CXXFLAGS += -DGEOM_GRID
$(info GEOM = grid)
else ifeq ($(GEOM), periph)
CXXFLAGS += -DGEOM_PERIPH
$(info GEOM = periph)
else
$(error GEOM must be defines as dome, periph, or grid)
endif

ifeq ($(TECHNOLOGY), teensy)
MAKE_PATH = teensy.mk
$(info TECHNOLOGY = teensy)
else
MAKE_PATH = sim.mk
$(info TECHNOLOGY = sim)
endif

include ${MAKE_PATH}
