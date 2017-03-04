# common
ARDUINO_LIBS = FastLED

# teensy3.6
BOARD_TAG 	 = teensy36
MONITOR_PORT = /dev/ttyACM0
include ${ARDMK_DIR}/Teensy.mk

# arduino nano
#BOARD_TAG 	 = nano
#BOARD_SUB    = atmega328
#MONITOR_PORT = /dev/ttyUSB0
#include ${ARDMK_DIR}/Arduino.mk
