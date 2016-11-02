CXX = g++
CXXFLAGS = -std=c++14
CXXLIBS = -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

##all: Timber TimerLowres
all: Timber

Timber: code/Timber.o
		$(CXX) $< -o $@ $(CXXLIBS)

##TimberLowres: lowres/Timber.o
##		$(CXX) $< -o $@ $(CXXLIBS)

code/%.o: %.cpp
		$(CXX) $< -o $@
		
##lowres/%.o: %.cpp
##		$(CXX) $< -o $@
		
clean:
##		rm Timber TimberLowres code/*.o lowres/*.o
		rm Timber code/*.o
