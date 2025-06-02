CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRC_COMMON = GestionnaireSysteme.cpp Sensor.cpp Mesure.cpp Attribut.cpp User.cpp PrivateUser.cpp
DEPS = GestionnaireSysteme.h Sensor.h Mesure.h Attribut.h User.h PrivateUser.h

APP_SRC = main.cpp $(SRC_COMMON)
TEST_SRC = main_test.cpp $(SRC_COMMON)

APP_OBJ = $(APP_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

APP_TARGET = airwatcher
TEST_TARGET = tests

all: $(APP_TARGET) $(TEST_TARGET)

$(APP_TARGET): $(APP_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o $(APP_TARGET) $(TEST_TARGET)
