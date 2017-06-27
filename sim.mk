CC = /usr/bin/g++
INC += -I.
INC += -IFastLEDEmulator
INC += -IArduinoEmulator
INC += -Ifixmath
OBJ = FastLEDEmulator/*.cpp ArduinoEmulator/*.cpp *.cpp fixmath/*.c
SIM_DIR = build-sim

ifeq ($(TECHNOLOGY), none)
OBJ += NoTech/*.cpp
INC += -INoTech
$(info TECHNOLOGY = none)
else
CXXFLAGS += -std=c++11 -g -DSIM `sdl-config --cflags --libs`
OBJ += QuickCG/*.cpp
INC += -IQuickCG
$(info TECHNOLOGY = quickcg)
endif

sim: $(OBJ)
	@mkdir -p $(SIM_DIR)
	$(CC) -o $(SIM_DIR)/bixi ${INC} $(OBJ) $(CXXFLAGS)

clean:
	@rm -rf $(SIM_DIR)
