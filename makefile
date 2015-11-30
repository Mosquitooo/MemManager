
target_dir = ./bin

all:
	@if [ ! -d ${target_dir} ]; then mkdir ${target_dir};fi

Test:MemTrace.o MemList.o MemTest.cpp
	@g++ $^ -o $@
	@rm -rf ${target_dir}/*.*
	@mv *.o ${target_dir}
	@mv $@ ${target_dir}
	@mv *.gch ${target_dir}

MemTrace.o: MemTrace.cpp MemTrace.h
	@g++ -c $^

MemList.o: MemList.cpp MemList.h
	@g++ -c $^

clean:
	rm -f ./bin/*.*