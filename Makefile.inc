# set the IBLIB environment variable to point to the libraries directory
# the default is the current directory
IBLIB ?= .

# use gnu compilers
CCC = gcc
CXX = g++

INCLUDES = -I. -I$(IBLIB)/ib_files/PosixSocketClient -I$(IBLIB)/ib_files/Shared -I/usr/local/include
LIBS = -L../ -L/usr/local/lib -L$(IBLIB)/lib -lm

CCFLAGS = -g -Wall
LDFLAGS = -g

.SUFFIXES: .cpp

################################################################################

.cpp.o:
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@


