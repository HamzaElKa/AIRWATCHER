CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC = main.cpp GestionnaireSysteme.cpp Sensor.cpp Mesure.cpp Attribut.cpp
OBJ = $(SRC:.cpp=.o)
DEPS = GestionnaireSysteme.h Sensor.h Mesure.h Attribut.h

TARGET = airwatcher

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)