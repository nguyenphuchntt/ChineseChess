###
###

EXEC = main

# build and assets directory
BUILD_DIR = build
ASSET_DIR = assets


#Sources 

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

#Includes

INCLUDES_DIR = include
INCLUDES := -I$(INCLUDES_DIR) -I$(INCLUDES_DIR)/SDL2

#C++ compiler settings

CXX = g++
CXXFLAGS = -std=c++17 -m64

#Linker flags

LDFLAGS = 

# Libraries to link

LDLIBS = -l"SDL2" -l"SDL2_image"

LDFLAGS += -static-libgcc -static-libstdc++
LDLIBS := -l"mingw32" -l"SDL2main" $(LDLIBS)
LIB_PATH = -L"include/lib"

EXEC := $(EXEC).exe

OUTPUT = $(BUILD_DIR)/$(EXEC)

.PHONY: all
all: $(OUTPUT)

$(OUTPUT): $(SRCS)
	$(CXX) $(LIB_PATH) -o $@ $^ $(LDLIBS) $(INCLUDES)

.PHONY: run
run: 
	./$(BUILD_DIR)/$(EXEC)

.PHONY: clean
clean:
	@echo Cleaning $(BUILD_DIR) directory
	rm $(OUTPUT)

