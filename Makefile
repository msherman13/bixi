#BOARD_TAG 	 = teensy36
#MONITOR_PORT = /dev/ttyACM0
BOARD_TAG 	 = nano
BOARD_SUB    = atmega328
MONITOR_PORT = /dev/ttyUSB0
ARDUINO_LIBS = FastLED
#include ${ARDMK_DIR}/Teensy.mk
include ${ARDMK_DIR}/Arduino.mk
