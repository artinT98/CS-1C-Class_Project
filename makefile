CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -std=c++11 -Wall

TARGET = hw06

SRC = hw06.cpp
OBJ = hw06.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ)

hw06.o: hw06.cpp BankAccount.h CD.h CheckingAccount.h SavingAccount.h Wrapper.h
	$(CXX) $(CXXFLAGS) -c hw06.cpp

clean:
	rm -f $(TARGET) $(OBJ)

tar:
	tar cf hw06.tar BankAccount.h  CD.h CheckingAccount.h SavingAccount.h Wrapper.h hw06.cpp hw06.scr makefile
