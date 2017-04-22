Object := ConsistencyHashTest

Include := ./
cflag := -std=c++11 -static -I$(Include)
srcs = $(wildcard *.cpp)
objs = $(patsubst %.cpp, %.o, $(srcs))

$(Object):$(objs)
	echo $(objs)
	g++ -o $@ $(cflag) $^

%.o:%.cpp
	g++ -o $@ $(cflag) -c  $^
	
.PHONY:clean
clean:
	rm *.o -f


