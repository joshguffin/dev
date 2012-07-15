# vim: set ft=make
#
# set the $CPPROOT environment variable to point to the directory containing lib/, src/, etc.
#
CPPROOT ?= .
IBLIB = $(CPPROOT)/library/

# use clang compilers
CCC = clang
CXX = clang++


## TODO: adding a library to the list of dependencies should
## add a line to the INCLUDES and LIBS

INCLUDES = -I. -I$(IBLIB)/includes/ -I/usr/local/include
LIBS = -L/usr/local/lib -L$(IBLIB)lib -lm

CCFLAGS = -g -Wall -DIB_USE_STD_STRING -Wno-switch
LDFLAGS = -g

.SUFFIXES: .cpp

################################################################################
# libib.a
################################################################################
ibOBJECTS = $(patsubst %.c,%.o,$(wildcard $(IBLIB)/ib/*.cpp))
ibLIBRARY = $(IBLIB)/lib/libib.a

$(ibOBJECTS):
	$(CXX) $(INCLUDES) $(CCFLAGS) $(LIBRS) -c $< -o $@

$(ibLIBRARY)_lib:
	ar rcs $(ibLIBRARY) $(ibOBJECTS)

################################################################################


