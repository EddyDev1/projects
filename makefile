CS: church_system.o
	g++ -o CS church_system.o

church_system.o: church_system.cpp
	g++ -std=c++20 -c church_system.cpp