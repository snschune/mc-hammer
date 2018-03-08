exec    = a.out
cc      = g++
opt     = -O0
cflags  = -std=c++14 $(opt)
srcdir  = ../

tests = $(patsubst %.cpp,%.tst,$(filter-out $(main), $(wildcard *.cpp)))

.PHONY : test clean

test :	$(objects) 
	@rm -f $(tests)
	@$(MAKE) -k $(tests)

%.tst : %.cpp
	@ $(cc) $(cflags) $(srcdir)*.o -I$(srcdir) -o $@ $<
	@ echo 'running test' $@
	@ ./$@

clean :
	rm -f $(tests)
