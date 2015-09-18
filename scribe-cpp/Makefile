.PHONY: force

PATH_INCLUDE_THRIFT= /usr/local/include/thrift
PATH_INCLUDE_BOOST=/usr/local/include
PATH_THRIFT= /usr/local/bin/thrift


LDLIBS=-lfb303 -lthrift -lstdc++
LDFLAGS=-Lfb303/cpp
CFLAGS=-fPIC
INCLUDE=-I$(PATH_INCLUDE_THRIFT) -I$(PATH_INCLUDE_BOOST) -I/usr/include 
LIBRARY=libscribe.a
SRCS=scribe_c.cpp $(wildcard gen-cpp/*.cpp) 
OBJS=$(SRCS:%.cpp=%.o)

DEBUG=-g3

all: $(LIBRARY)
	@true

%.o:	
	$(CC) $(CFLAGS) -c -static $(INCLUDE) $(DEBUG) $*.cpp -o $*.o

$(LIBRARY): $(OBJS)
	ar crv libscribe.a $(OBJS) 

gen-thrift:
	$(PATH_THRIFT) --gen cpp fb303.thrift 
	$(PATH_THRIFT) --gen cpp scribe.thrift
	rm -f gen-cpp/*skeleton*
	
test: $(LIBRARY) test.c
	$(CC) test.c $(INCLUDE) $(DEBUG) $(LDFLAGS) $(LDLIBS) $(LIBRARY) -o test

clean: force
	rm -f *~ $(OBJS) *.a
