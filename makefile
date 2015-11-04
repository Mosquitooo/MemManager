

Test:MemTrace.o MemList.o MemTest.cpp
	g++ $^ -o Test

MemTrace.o: MemTrace.cpp MemTrace.h
	g++ -c $^

MemList.o: MemList.cpp MemList.h
	g++ -c $^

clean:
	rm -f *.o
	rm -f Test