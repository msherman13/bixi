# common
ARDUINO_LIBS = FastLED

# teensy3.6
BOARD_TAG 	 = teensy36
MONITOR_PORT = /dev/ttyACM0

ifeq ($(TECHNOLOGY), teensy)
	MAKE_PATH=${ARDMK_DIR}/Teensy.mk
else
	MAKE_PATH = sim.mk
endif

include ${MAKE_PATH}
