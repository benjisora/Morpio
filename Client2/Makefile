CXX = g++
 
WD = $(shell pwd)
BUILD_DIR = build
 
SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))
 
EXE = Morpio
 
CXXFLAGS = -std=c++11 -Wall -Wextra -Wfatal-errors -fno-rtti 
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
 
all: $(EXE)
 
-include $(OBJ:.o=.d)
 
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS) -o $@
 
$(BUILD_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	$(CXX) $(CXXFLAGS) $< -MM -MT$@ -MF$(@:.o=.d)
 
clean:
	rm -rf $(EXE) $(BUILD_DIR)
	
