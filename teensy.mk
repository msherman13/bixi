PORT = /dev/ttyACM0

geom:
	./scripts/teensy_define.py /opt/arduino/hardware/teensy/avr/boards.txt ${CXXFLAGS}

upload: geom
	arduino --board teensy:avr:teensy36 --upload bixi.ino --port ${PORT}
   
#   --pref build.path=build-teensy36
