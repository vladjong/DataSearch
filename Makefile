CC = g++
FLAGS = -lgtest -lstdc++ -std=c++17
SOURCES = model.cpp \
		main.cpp \
		view.cpp

HEDERS 	= model.h \
		controller.h \
		view.h


all: install

install:
	$(CC) $(SOURCES) -o app
	./app

cpplint:
	cp linters/CPPLINT.cfg . && python3 linters/cpplint.py --extensions=cpp $(SOURCES) $(HEDERS)

clean:
	rm -rf app
	rm -rf CPPLINT.cfg


# test: g++ test.cpp $(FLAGS) $(WCHECK) -o test