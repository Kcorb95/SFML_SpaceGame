CXX = g++
CXXFLAGS = -std=c++14
CXXLIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: GameProg1 GameProg1

GameProg1: src/Action.o src/Enemy.o src/FarOut.o \
			 src/Player.o src/ScreenGame.o src/ScreenMenu.o src/Weapon.o
	$(CXX) -O3 $? -o $@ $(CXXLIBS)

src/%.o: %.cpp %.h
	$(CXX) $< -o $@

clean:
	rm GameProg1 src/*.o

