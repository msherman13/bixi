PORT = /dev/ttyACM0
upload:
	arduino --board teensy:avr:teensy36 --upload bixi.ino --port ${PORT}
