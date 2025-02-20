CXX = g++
CXXFLAGS = -Wall -pthread
TARGET = linuxmanager
Source = $(wildcard ./Process/*.cpp ./System/*.cpp) main.cpp

$(TARGET): 
	$(CXX) $(CXXFLAGS) $(Source) -o $(TARGET) 
