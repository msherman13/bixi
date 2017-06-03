# common
ARDUINO_LIBS = FastLED

# teensy3.6
BOARD_TAG 	 = teensy36
MONITOR_PORT = /dev/ttyACM0

ifeq ($(TECHNOLOGY), teensy)
MAKE_PATH=${ARDMK_DIR}/Teensy.mk
$(info TECHNOLOGY = teensy)
else
MAKE_PATH = sim.mk
$(info TECHNOLOGY = sim)
endif

ifeq ($(GEOM), dome)
CXXFLAGS += -DGEOM_DOME
$(info GEOM = dome)
else ifeq ($(GEOM), grid)
CXXFLAGS += -DGEOM_GRID
$(info GEOM = grid)
else ifeq ($(GEOM), periph)
CXXFLAGS += -DGEOM_PERIPH
$(info GEOM = periph)
else
$(error GEOM must be defines as dome or periph)
endif

include ${MAKE_PATH}
