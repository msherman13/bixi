CC = /usr/bin/g++
CXXFLAGS = -I. -std=c++11 -g
OBJ = FastLEDEmulator/*.cpp ArduinoEmulator/*.cpp *.cpp
SIM_DIR = build-sim
INC += -IFastLEDEmulator
INC += -IArduinoEmulator

sim: $(OBJ)
	mkdir -p $(SIM_DIR)
	$(CC) -o $(SIM_DIR)/bixi $(OBJ) ${INC} $(CXXFLAGS)

clean:
	rm -rf $(SIM_DIR)
