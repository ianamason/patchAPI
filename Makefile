#
#
# This Makefile written by iam.
#


ifeq ($(DYNINST),)
$(error DYNINST is not set)
endif

ifeq ($(BOOST),)
$(error BOOST is not set)
endif

ifeq ($(TBB),)
$(error TBB is not set)
endif

CXX = g++
CXXFLAGS = -g -Wall -faligned-new

all: main

main: main.o
	$(CXX) $(CXXFLAGS) -L$(DYNINST)/lib -o main main.o  -ldyninstAPI -lsymtabAPI -lparseAPI -lpatchAPI -linstructionAPI -lcommon


main.o: main.cpp
	$(CXX) $(CXXFLAGS) -I$(BOOST)/include  -I$(TBB)/include -I$(DYNINST)/include -c main.cpp

hybrid_main: hybrid_main.o
	$(CXX) $(CXXFLAGS) -L$(DYNINST)/lib -o hybrid_main hybrid_main.o  -ldyninstAPI -lpatchAPI -linstructionAPI -lcommon

hybrid_main.o: hybrid_main.cpp
	$(CXX) $(CXXFLAGS) -I$(BOOST)/include  -I$(TBB)/include -I$(DYNINST)/include -c hybrid_main.cpp

test: main mutatee/main
	./main ./mutatee/main ./mutatee/main.out

hybrid_test: hybrid_main mutatee/main
	./hybrid_main ./mutatee/main ./mutatee/main.out

mutatee/main:
	make -C mutatee


clean:
	rm -f main hybrid_main  *.o *~
	make -C mutatee clean
