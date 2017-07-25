PORT = /dev/ttyACM0

ifeq ($(PLATFORM), mac)
BOARDS_CONFIG=/Applications/Arduino.app/Contents/Java/hardware/teensy/avr/boards.txt
else
BOARDS_CONFIG=/opt/arduino/hardware/teensy/avr/boards.txt
endif

geom:
	./scripts/teensy_define.py ${PLATFORM} ${BOARDS_CONFIG} ${CXXFLAGS}

upload: geom
	arduino --board teensy:avr:teensy36 --upload bixi.ino --port ${PORT}
   
#   --pref build.path=build-teensy36
