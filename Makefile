exec    = a.out
cc      = g++
opt     = -g 
cflags  = -std=c++11 $(opt) 
testdir = Testing
pwd     = $(shell pwd)

main    = Main.cpp
objects = $(patsubst %.cpp,%.o,$(filter-out $(main), $(wildcard *.cpp)))

.PHONY : all test clean

all :	$(objects) $(exec) test

test :
	@ cd $(testdir) && $(MAKE)

%.o : %.cpp
	$(cc) $(cflags) -c $<

$(exec) : $(main)
	@rm -f $(exec)
	$(cc) $(cflags) $(objects) $< -o $@

clean :
	rm -f $(objects) $(exec) Main.o
	@ cd  $(testdir) && $(MAKE) clean
