CC = /usr/bin/g++
CXXFLAGS = -I. -std=c++11 -g
OBJ = FastLEDEmulator/*.cpp ArduinoEmulator/*.cpp *.cpp QuickCG/*.cpp
SIM_DIR = build-sim
INC += -IFastLEDEmulator
INC += -IArduinoEmulator
INC += -IQuickCG

sim: $(OBJ)
	mkdir -p $(SIM_DIR)
	$(CC) -o $(SIM_DIR)/bixi $(OBJ) ${INC} $(CXXFLAGS)

clean:
	rm -rf $(SIM_DIR)
